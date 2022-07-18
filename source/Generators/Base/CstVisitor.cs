using System;
using System.Collections.Generic;
using System.Linq;
using XCG.Parsing;

namespace XCG.Generators.Base;

public class CstVisitor
{
    private readonly Parser _parser;

    public CstVisitor(Parser parser)
    {
        _parser = parser;
    }

    public IEnumerable<Group> Accumulate()
    {
        var tokenizer = new Group(Constants.Groups.Tokenizer);
        CreateSkipFunction(tokenizer);
        throw new NotImplementedException();
    }

    private void CreateSkipFunction(Group group)
    {
        var contents = group.State(Constants.States.ParsingContents, EType.CharacterCollection);
        var contentsLength = group.State(Constants.States.ParsingContentsLength, EType.Size);
        var offset = group.State(Constants.States.ParsingOffset, EType.FileOffset);
        var column = group.State(Constants.States.ParsingColumn, EType.FileOffset);
        var line = group.State(Constants.States.ParsingLine, EType.FileOffset);
        group.AddFunction(Constants.Functions.Skip, EType.Void, (function) =>
        {
            void DefaultSkip(Action<CaseCodeStatement>? defaultCase)
            {
                function.AddWhile(contentsLength.GreaterThan(offset), (whileStatement) =>
                {
                    var c = whileStatement.AddVariable(
                        "c", EType.Character, contents.ArrayAccess(offset));
                    whileStatement.AddSwitch(c.Ref(), (switchStatement) =>
                    {
                        switchStatement.AddCase(new[] {'\t', ' ', '\r'}, (caseStatement) =>
                        {
                            caseStatement.AddExpression(column.Increase());
                            caseStatement.AddExpression(offset.Increase());
                        });
                        switchStatement.AddCase('\n', (caseStatement) =>
                        {
                            caseStatement.AddExpression(line.Increase());
                            caseStatement.AddExpression(column.Assign(1));
                            caseStatement.AddExpression(offset.Increase());
                        });
                        if (defaultCase is not null)
                            switchStatement.AddCaseDefault(defaultCase);
                        else
                            switchStatement.AddCaseDefault((caseStatement) =>
                            {
                                caseStatement.AddExpression(column.Increase());
                                caseStatement.AddExpression(offset.Increase());
                            });
                    });
                });
            }

            DefaultSkip((caseStatement) =>
            {
                if (_parser.Comments.Any())
                {
                    var wasMatched = caseStatement.AddVariable("commentMatched", false);
                    foreach (var parserComment in _parser.Comments)
                    {
                        var start = parserComment.Start.LowerTokenString();
                        var end = parserComment.End.LowerTokenString();
                        caseStatement.AddPositiveLookAhead(group, start, (positiveLookAhead) =>
                        {
                            positiveLookAhead.AddExpression(wasMatched.Ref().Assign(true));
                            // ToDo: Add remaining stuff
                        });
                    }
                }
            });
        });
    }
}

public static class StringExtensions
{
    public static string LowerTokenString(this string? str)
    {
        return str?.ToLowerInvariant() switch
        {
            "eof" => "\0",
            "eol" => "\n",
            null => throw new NullReferenceException("Failed to get value of token string"),
            _ => str,
        };
    }
    public static string LowerTokenString(this string? str, string defaultValue)
    {
        return (str?.ToLowerInvariant() ?? defaultValue) switch
        {
            "eof" => "\0",
            "eol" => "\n",
            _ => str ?? defaultValue,
        };
    }
}