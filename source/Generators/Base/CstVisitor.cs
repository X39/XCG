using System.Collections.Generic;
using System.Linq;
using XCG.Generators.Base.Contracts;
using XCG.Generators.Base.Enums;
using XCG.Generators.Base.Expressions;
using XCG.Generators.Base.Extensions;
using XCG.Generators.Base.Parts;
using XCG.Generators.Base.Statements;
using XCG.Parsing;

namespace XCG.Generators.Base;

public class CstVisitor
{
    private readonly Parser _parser;
    private readonly List<DelayedFunctionReferences> _delayedFunctionReferences = new();
    public IReadOnlyCollection<Group> Groups => _groups;
    private readonly List<Group> _groups = new();

    public CstVisitor(Parser parser)
    {
        _parser = parser;
    }

    public void Accumulate()
    {
        var tokenFunctions = new List<(Token, Function)>();
        CreateContents(tokenFunctions);
        foreach (var (token, function) in tokenFunctions)
        {
            foreach (var delayedFunctionReference in _delayedFunctionReferences.Where((q) => q.Token == token))
            {
                delayedFunctionReference.SetFunction(function);
            }
        }
    }

    private void CreateContents(ICollection<(Token, Function)> tokenFunctions)
    {
        var tokenizer = new Group(Constants.Groups.Tokenizer);
        _groups.Add(tokenizer);
        CreateSkipFunction(tokenizer);
        foreach (var parserToken in _parser.Tokens)
        {
            var function = CreateTokenFunction(tokenizer, parserToken);
            tokenFunctions.Add((parserToken, function));
        }
    }

    private Function CreateTokenFunction(Group group, Token token)
    {
        return group.AddFunction(token.Identifier, EType.OptionalSize, (function) =>
        {
            var resetData = ResetData.Create(group, function);
            foreach (var tokenStatement in token.Children)
            {
                switch (tokenStatement)
                {
                    case Parsing.TokenStatements.Require require:
                    {
                        VariableStatement? countVariable = null;
                        ICodeExpression condition = group.CurrentCharacter()
                            .NotEqual(new ValueExpression('\0'));
                        if (require.Range.To < int.MaxValue)
                        {
                            countVariable = function.AddVariable(
                                Constants.Variables.Count,
                                EType.Size,
                                new ValueExpression(0));
                            condition = condition.And(countVariable.Ref()
                                .LessThan(new ValueExpression(require.Range.To)));
                        }

                        function.AddWhile(condition, (whileCodeStatement) =>
                        {
                            foreach (var part in require.Parts)
                            {
                                switch (part)
                                {
                                    case Word word:
                                    {
                                        whileCodeStatement.AddSinglePositiveLookAhead(
                                            group,
                                            word.Text,
                                            (ifCodeStatement) =>
                                            {
                                                if (countVariable is not null)
                                                    ifCodeStatement.AddExpression(countVariable.Ref().Increment());
                                                ifCodeStatement.ConsumeCharacters(group, word.Text.Length);
                                                ifCodeStatement.AddContinue();
                                            });
                                        break;
                                    }
                                    case CharacterRange range:
                                        var expression = new ValueExpression(range.Start)
                                            .LessThanOrEqual(group.CurrentCharacter())
                                            .And(group.CurrentCharacter()
                                                .LessThanOrEqual(new ValueExpression(range.End)));
                                        whileCodeStatement.AddIf(require.Negated ? expression.Not() : expression,
                                            (ifCodeStatement) =>
                                            {
                                                if (countVariable is not null)
                                                    ifCodeStatement.AddExpression(countVariable.Ref().Increment());
                                                ifCodeStatement.ConsumeCharacter(group);
                                                ifCodeStatement.AddContinue();
                                            });
                                        break;
                                    case Reference {Referred: Token referredToken}:
                                    {
                                        var result = whileCodeStatement.AddVariable("result", EType.OptionalSize,
                                            CreateDelayedFunctionReference(referredToken).Call());
                                        whileCodeStatement.AddIf(result.Ref().Access(EProperty.HasValue),
                                            (ifCodeStatement) =>
                                            {
                                                if (countVariable is not null)
                                                    ifCodeStatement.AddExpression(countVariable.Ref().Increment());
                                                ifCodeStatement.ConsumeCharacters(group,
                                                    result.Ref().Access(EProperty.GetValue));
                                                ifCodeStatement.AddContinue();
                                            });
                                        break;
                                    }
                                    case Reference:
                                        throw new FatalException("Unimplemented require part");
                                    default:
                                        throw new FatalException("Unimplemented require part");
                                }
                            }

                            whileCodeStatement.AddBreak();
                        });


                        if (countVariable is not null && require.Range.From > 0)
                        {
                            function.AddIf(
                                countVariable.Ref().LessThan(new ValueExpression(require.Range.From)),
                                (ifCodeStatement) =>
                                {
                                    resetData.PerformReset(ifCodeStatement);
                                    // $@"trace(""Returning EmptyClosure on {token.Identifier}"", {Constants.DepthVariable});"
                                    ifCodeStatement.AddReturn(new EmptyValueExpression(EType.OptionalSize));
                                });
                        }

                        break;
                    }
                    case Parsing.TokenStatements.Backtrack backtrack:
                    {
                        VariableStatement? countVariable = null;
                        var offset = group.State(Constants.States.ParsingOffset, EType.Size);
                        ICodeExpression condition = offset.GreaterThanOrEqual(new ValueExpression(0));
                        if (backtrack.Range.To < int.MaxValue)
                        {
                            countVariable = function.AddVariable(
                                Constants.Variables.Count,
                                EType.Size,
                                new ValueExpression(0));
                            condition = condition.And(countVariable.Ref()
                                .LessThan(new ValueExpression(backtrack.Range.To)));
                        }


                        function.AddWhile(condition, (whileCodeStatement) =>
                        {
                            foreach (var part in backtrack.Parts)
                            {
                                switch (part)
                                {
                                    case Word word:
                                    {
                                        whileCodeStatement.AddSingleNegativeLookAhead(
                                            group,
                                            word.Text,
                                            (ifCodeStatement) =>
                                            {
                                                if (countVariable is not null)
                                                    ifCodeStatement.AddExpression(countVariable.Ref().Decrement());
                                                ifCodeStatement.AddContinue();
                                            });
                                        break;
                                    }
                                    case CharacterRange range:
                                        var expression = new ValueExpression(range.Start)
                                            .LessThanOrEqual(group.CurrentCharacter(-1))
                                            .And(group.CurrentCharacter(-1)
                                                .LessThanOrEqual(new ValueExpression(range.End)));
                                        whileCodeStatement.AddIf(backtrack.Negated
                                                ? expression.Not()
                                                : expression,
                                            (ifCodeStatement) =>
                                            {
                                                if (countVariable is not null)
                                                    ifCodeStatement.AddExpression(countVariable.Ref().Increment());
                                                ifCodeStatement.ConsumeCharacter(group);
                                                ifCodeStatement.AddBreak();
                                            });
                                        break;
                                    default:
                                        throw new FatalException("Unimplemented backtrack part");
                                }
                            }
                        });
                        if (countVariable is not null)
                        {
                            function.AddIf(
                                backtrack.Range.From > 0
                                    ? countVariable.Ref().GreaterThanOrEqual(new ValueExpression(backtrack.Range.From))
                                    : countVariable.Ref().NotEqual(new ValueExpression(backtrack.Range.From)),
                                (ifCodeStatement) =>
                                {
                                    resetData.PerformReset(ifCodeStatement);
                                    // $@"trace(""Returning EmptyClosure on {token.Identifier}"", {Constants.DepthVariable});"
                                    ifCodeStatement.AddReturn(new EmptyValueExpression(EType.OptionalSize));
                                });
                        }

                        break;
                    }
                    default:
                        throw new FatalException("Unimplemented TokenStatement");
                }
            }

            var temporaryOffset = function.AddVariable(
                Constants.VariablePrefixes.Temporary + Constants.States.ParsingOffset,
                EType.Size,
                group.State(Constants.States.ParsingOffset, EType.FileOffset));
            resetData.PerformReset(function);
            function.AddReturn(temporaryOffset.Ref());
        });
    }

    private FunctionReference CreateDelayedFunctionReference(Token token)
    {
        var functionReference = new DelayedFunctionReferences(token);
        _delayedFunctionReferences.Add(functionReference);
        return functionReference;
    }

    private void CreateSkipFunction(Group group)
    {
        group.AddFunction(Constants.Functions.Skip, EType.Void, (function) =>
        {
            function.AddWhile(new ValueExpression(true), (whileStatement) =>
            {
                whileStatement.ConsumeCharacter(group, (caseStatement) =>
                {
                    if (!_parser.Comments.Any())
                    {
                        caseStatement.AddReturn();
                        return;
                    }

                    var wasMatched = caseStatement.AddVariable("commentMatched", false);
                    foreach (var parserComment in _parser.Comments)
                    {
                        var start = parserComment.Start.LowerTokenString();
                        var end = parserComment.End.LowerTokenString();
                        caseStatement.AddSinglePositiveLookAhead(group, start, (positiveLookAhead) =>
                        {
                            positiveLookAhead.AddExpression(wasMatched.Ref().Assign(new ValueExpression(true)));
                            positiveLookAhead.ConsumeCharacters(group, start.Length);
                            positiveLookAhead.AddLoopingNegativePositiveLookAhead(group, end,
                                (whileCodeStatement) => whileCodeStatement.ConsumeCharacter(group));
                            positiveLookAhead.ConsumeCharacters(group, end.Length);
                        });
                    }

                    caseStatement.AddIf(wasMatched.Ref().Not(), (ifCodeStatement) => ifCodeStatement.AddReturn());
                });
            });
        });
    }

    private class DelayedFunctionReferences : FunctionReference
    {
        public readonly Token Token;

        public DelayedFunctionReferences(Token token) : base(null!)
        {
            Token = token;
        }

        public void SetFunction(Function function) => Function = function;
    }
}