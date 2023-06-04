using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Diagnostics.CodeAnalysis;
using System.Linq;
using JetBrains.Annotations;
using X39.Systems.XCG.Generators.Base.Contracts;
using X39.Systems.XCG.Generators.Base.Enums;
using X39.Systems.XCG.Generators.Base.Expressions;
using X39.Systems.XCG.Generators.Base.Parts;
using X39.Systems.XCG.Generators.Base.Statements;
using X39.Util;

namespace X39.Systems.XCG.Generators.Base.Extensions;

public static class CodeStatementHostExtensions
{
    public static ContinueStatement AddContinue(
        this ICodeStatementsHost self)
    {
        Debug.Assert(self
                .FlattenParentHierarchy((q) => q.Parent)
                .Any(x => x is Meta.ILoopStatement),
            "AddContinue can only be used if at least one parent is a loop.");
        var statement = new ContinueStatement(self);
        self.Add(statement);
        return statement;
    }

    public static BreakStatement AddBreak(
        this ICodeStatementsHost self)
    {
        Debug.Assert(self
                .FlattenParentHierarchy((q) => q.Parent)
                .Any(x => x is Meta.ILoopStatement or SwitchCodeStatement),
            "AddBreak can only be used if at least one parent is a loop or a switch.");
        var statement = new BreakStatement(self);
        self.Add(statement);
        return statement;
    }

    public static ForCodeStatement AddFor(
        this ICodeStatementsHost self,
        int count,
        Action<ForCodeStatement, VariableReference> func)
    {
        var statement = new ForCodeStatement(self,
            (forStatement) => new VariableStatement(forStatement, "i", EType.Integer, new ValueExpression(0)),
            (_, variable) => variable.LessThan(new ValueExpression(count)),
            (_, variable) => variable.Increment());
        self.Add(statement);
        func(statement, statement.Variable.Ref());
        return statement;
    }

    public static ForCodeStatement AddFor(
        this ICodeStatementsHost self,
        Func<ForCodeStatement, VariableStatement> variableFactory,
        Func<ForCodeStatement, VariableReference, ICodeExpression> conditionFactory,
        Func<ForCodeStatement, VariableReference, ICodeExpression> stepFactory,
        Action<ForCodeStatement, VariableReference> func)
    {
        var statement = new ForCodeStatement(self,
            variableFactory,
            conditionFactory,
            stepFactory);
        self.Add(statement);
        func(statement, statement.Variable.Ref());
        return statement;
    }

    public static ReturnStatement AddReturn(
        this ICodeStatementsHost self,
        ICodeExpression? expression = null)
    {
        var statement = new ReturnStatement(self, expression);
        self.Add(statement);
        return statement;
    }

    public static IfCodeStatement AddIf(
        this ICodeStatementsHost self,
        ICodeExpression condition,
        Action<IfCodeStatement> func)
    {
        var statement = new IfCodeStatement(self, condition);
        self.Add(statement);
        func(statement);
        return statement;
    }

    public static ElseIfCodeStatement ElseIf(
        this ElseIfCodeStatement self,
        ICodeExpression condition,
        Action<ElseIfCodeStatement> func)
    {
        var statement = new ElseIfCodeStatement(self.Parent, condition);
        self.Parent.Add(statement);
        func(statement);
        return statement;
    }

    public static ElseCodeStatement Else(
        this ElseIfCodeStatement self,
        Action<ElseCodeStatement> func)
    {
        var statement = new ElseCodeStatement(self.Parent);
        self.Parent.Add(statement);
        func(statement);
        return statement;
    }

    public static ElseIfCodeStatement ElseIf(
        this IfCodeStatement self,
        ICodeExpression condition,
        Action<ElseIfCodeStatement> func)
    {
        var statement = new ElseIfCodeStatement(self.Parent, condition);
        self.Parent.Add(statement);
        func(statement);
        return statement;
    }

    public static ElseCodeStatement Else(
        this IfCodeStatement self,
        Action<ElseCodeStatement> func)
    {
        var statement = new ElseCodeStatement(self.Parent);
        self.Parent.Add(statement);
        func(statement);
        return statement;
    }

    public static WhileCodeStatement AddWhile(
        this ICodeStatementsHost self,
        ICodeExpression condition,
        Action<WhileCodeStatement> func)
    {
        var statement = new WhileCodeStatement(self, condition);
        self.Add(statement);
        func(statement);
        return statement;
    }

    public static SwitchCodeStatement AddSwitch(
        this ICodeStatementsHost self,
        ICodeExpression switchOn,
        Action<SwitchCodeStatement> func)
    {
        var statement = new SwitchCodeStatement(self, switchOn);
        self.Add(statement);
        func(statement);
        return statement;
    }

    public static CodeExpressionStatement AddExpression(
        this ICodeStatementsHost self,
        ICodeExpression expression)
    {
        var statement = new CodeExpressionStatement(self, expression);
        self.Add(statement);
        return statement;
    }


    public static CaseCodeStatement AddCase(
        this SwitchCodeStatement self,
        IEnumerable<ValueExpression> values,
        Action<CaseCodeStatement> func)
    {
        var statement = new CaseCodeStatement(self, values);
        ((ICollection<ICodeStatement>) self).Add(statement);
        func(statement);
        return statement;
    }

    public static CaseCodeStatement AddCaseDefault(
        this SwitchCodeStatement self,
        Action<CaseCodeStatement> func)
    {
        var statement = new CaseCodeStatement(self, Enumerable.Empty<ValueExpression>());
        ((ICollection<ICodeStatement>) self).Add(statement);
        func(statement);
        return statement;
    }

    public static CaseCodeStatement AddCase(
        this SwitchCodeStatement self,
        ValueExpression value,
        Action<CaseCodeStatement> func)
    {
        var statement = new CaseCodeStatement(self, value);
        ((ICollection<ICodeStatement>) self).Add(statement);
        func(statement);
        return statement;
    }

    public static CaseCodeStatement AddCase<T>(
        this SwitchCodeStatement self,
        IEnumerable<T> values,
        Action<CaseCodeStatement> func)
        where T : struct
    {
        var statement = new CaseCodeStatement(self, values.Select((value) => new ValueExpression(value)));
        ((ICollection<ICodeStatement>) self).Add(statement);
        func(statement);
        return statement;
    }

    public static CaseCodeStatement AddCase<T>(
        this SwitchCodeStatement self,
        T value,
        Action<CaseCodeStatement> func)
        where T : struct
    {
        var statement = new CaseCodeStatement(self, new ValueExpression(value));
        ((ICollection<ICodeStatement>) self).Add(statement);
        func(statement);
        return statement;
    }


    public static VariableStatement AddVariable(
        this ICodeStatementsHost self,
        string identifier,
        EType type,
        ICodeExpression initialValue)
    {
        var statement = new VariableStatement(self, identifier, type, initialValue);
        self.Add(statement);
        return statement;
    }

    public static VariableStatement AddVariable(
        this ICodeStatementsHost self,
        string identifier,
        bool initialValue)
    {
        var statement = new VariableStatement(self, identifier, EType.Boolean, new ValueExpression(initialValue));
        self.Add(statement);
        return statement;
    }

    public static VariableStatement AddVariable(
        this ICodeStatementsHost self,
        string identifier,
        int initialValue)
    {
        var statement = new VariableStatement(self, identifier, EType.Integer, new ValueExpression(initialValue));
        self.Add(statement);
        return statement;
    }

    #region Token extensions

    /// <summary>
    /// Allows to add a negative-lookahead to <paramref name="self"/>,
    /// checking whether <paramref name="match"/> can be matched at this point.
    /// </summary>
    /// <param name="self">The container to add the lookahead to.</param>
    /// <param name="group">
    /// The <see cref="Group"/> that holds the <see cref="State"/> for
    /// <see cref="Constants.States.ParsingContents"/> and <see cref="Constants.States.ParsingOffset"/>.
    /// </param>
    /// <param name="match">
    /// The text to match against.
    /// </param>
    /// <param name="func">
    /// The function to call if <paramref name="match"/> is matched.
    /// </param>
    /// <returns>
    /// The <see cref="IfCodeStatement"/> that was created. 
    /// </returns>
    public static ICodeStatementsHost AddSingleNegativeLookAhead(
        this ICodeStatementsHost self,
        Group group,
        string match,
        Action<IfCodeStatement> func)
    {
        var contents = group.State(Constants.States.ParsingContents, EType.CharacterCollection);
        var offset = group.State(Constants.States.ParsingOffset, EType.FileOffset);

        ICodeExpression expression = offset.LessThanOrEqual(offset.Minus(new ValueExpression(match.Length)));
        for (var i = 0; i < match.Length; i++)
        {
            expression = expression.And(
                contents.ArrayAccess(offset.Minus(new ValueExpression(match.Length - i)))
                    .Equal(new ValueExpression(match[i])));
        }

        return self.AddIf(expression, func);
    }

    /// <summary>
    /// Allows to add a negative-lookahead to <paramref name="self"/>,
    /// checking whether <paramref name="match"/> can be matched at this point.
    /// </summary>
    /// <param name="self">The container to add the lookahead to.</param>
    /// <param name="group">
    /// The <see cref="Group"/> that holds the <see cref="State"/> for
    /// <see cref="Constants.States.ParsingContents"/> and <see cref="Constants.States.ParsingOffset"/>.
    /// </param>
    /// <param name="match">
    /// The text to match against.
    /// </param>
    /// <param name="func">
    /// The function to call if <paramref name="match"/> is matched.
    /// </param>
    /// <returns>
    /// The <see cref="WhileCodeStatement"/> that was created. 
    /// </returns>
    public static ICodeStatementsHost AddLoopingNegativeLookAhead(
        this ICodeStatementsHost self,
        Group group,
        string match,
        Action<WhileCodeStatement> func)
    {
        var contents = group.State(Constants.States.ParsingContents, EType.CharacterCollection);
        var offset = group.State(Constants.States.ParsingOffset, EType.FileOffset);

        ICodeExpression expression = offset.LessThanOrEqual(offset.Minus(new ValueExpression(match.Length)));
        for (var i = 0; i < match.Length; i++)
        {
            expression = expression.And(
                contents.ArrayAccess(offset.Minus(new ValueExpression(match.Length - i)))
                    .Equal(new ValueExpression(match[i])));
        }

        return self.AddWhile(expression, func);
    }

    /// <summary>
    /// Allows to add a negative-lookahead to <paramref name="self"/>,
    /// checking whether <paramref name="match"/> can not be matched at this point.
    /// </summary>
    /// <param name="self">The container to add the lookahead to.</param>
    /// <param name="group">
    /// The <see cref="Group"/> that holds the <see cref="State"/> for
    /// <see cref="Constants.States.ParsingContents"/> and <see cref="Constants.States.ParsingOffset"/>.
    /// </param>
    /// <param name="match">
    /// The text to match against.
    /// </param>
    /// <param name="func">
    /// The function to call if <paramref name="match"/> is matched.
    /// </param>
    /// <returns>
    /// The <see cref="IfCodeStatement"/> that was created. 
    /// </returns>
    public static ICodeStatementsHost AddSingleNegativeNegativeLookAhead(
        this ICodeStatementsHost self,
        Group group,
        string match,
        Action<IfCodeStatement> func)
    {
        var contents = group.State(Constants.States.ParsingContents, EType.CharacterCollection);
        var offset = group.State(Constants.States.ParsingOffset, EType.FileOffset);

        ICodeExpression expression = offset.LessThanOrEqual(offset.Minus(new ValueExpression(match.Length)));
        for (var i = 0; i < match.Length; i++)
        {
            expression = expression.And(
                contents.ArrayAccess(offset.Minus(new ValueExpression(match.Length - i)))
                    .Equal(new ValueExpression(match[i])));
        }

        return self.AddIf(expression.Not(), func);
    }

    /// <summary>
    /// Allows to add a negative-lookahead to <paramref name="self"/>,
    /// checking whether <paramref name="match"/> can not be matched at this point.
    /// </summary>
    /// <param name="self">The container to add the lookahead to.</param>
    /// <param name="group">
    /// The <see cref="Group"/> that holds the <see cref="State"/> for
    /// <see cref="Constants.States.ParsingContents"/> and <see cref="Constants.States.ParsingOffset"/>.
    /// </param>
    /// <param name="match">
    /// The text to match against.
    /// </param>
    /// <param name="func">
    /// The function to call if <paramref name="match"/> is matched.
    /// </param>
    /// <returns>
    /// The <see cref="WhileCodeStatement"/> that was created. 
    /// </returns>
    public static ICodeStatementsHost AddLoopingNegativeNegativeLookAhead(
        this ICodeStatementsHost self,
        Group group,
        string match,
        Action<WhileCodeStatement> func)
    {
        var contents = group.State(Constants.States.ParsingContents, EType.CharacterCollection);
        var offset = group.State(Constants.States.ParsingOffset, EType.FileOffset);

        ICodeExpression expression = offset.LessThanOrEqual(offset.Minus(new ValueExpression(match.Length)));
        for (var i = 0; i < match.Length; i++)
        {
            expression = expression.And(
                contents.ArrayAccess(offset.Minus(new ValueExpression(match.Length - i)))
                    .Equal(new ValueExpression(match[i])));
        }

        return self.AddWhile(expression.Not(), func);
    }

    /// <summary>
    /// Allows to add a positive-lookahead to <paramref name="self"/>,
    /// checking whether <paramref name="match"/> can be matched at this point.
    /// </summary>
    /// <param name="self">The container to add the lookahead to.</param>
    /// <param name="group">
    /// The <see cref="Group"/> that holds the <see cref="State"/> for
    /// <see cref="Constants.States.ParsingContents"/> and <see cref="Constants.States.ParsingOffset"/>.
    /// </param>
    /// <param name="match">
    /// The text to match against.
    /// </param>
    /// <param name="func">
    /// The function to call if <paramref name="match"/> is matched.
    /// </param>
    /// <returns>
    /// The <see cref="IfCodeStatement"/> that was created. 
    /// </returns>
    public static ICodeStatementsHost AddSinglePositiveLookAhead(
        this ICodeStatementsHost self,
        Group group,
        string match,
        Action<IfCodeStatement> func)
    {
        var contents = group.State(Constants.States.ParsingContents, EType.CharacterCollection);
        var offset = group.State(Constants.States.ParsingOffset, EType.FileOffset);

        ICodeExpression expression = contents.Access(EProperty.CharacterCollectionLength)
            .GreaterThan(offset.Plus(new ValueExpression(match.Length)));
        for (var i = 0; i < match.Length; i++)
        {
            expression = expression.And(
                contents.ArrayAccess(offset.Plus(new ValueExpression(i)))
                    .Equal(new ValueExpression(match[i])));
        }

        return self.AddIf(expression, func);
    }

    /// <summary>
    /// Allows to add a positive-lookahead to <paramref name="self"/>,
    /// checking whether <paramref name="match"/> can be matched at this point.
    /// </summary>
    /// <param name="self">The container to add the lookahead to.</param>
    /// <param name="group">
    /// The <see cref="Group"/> that holds the <see cref="State"/> for
    /// <see cref="Constants.States.ParsingContents"/> and <see cref="Constants.States.ParsingOffset"/>.
    /// </param>
    /// <param name="match">
    /// The text to match against.
    /// </param>
    /// <param name="func">
    /// The function to call if <paramref name="match"/> is matched.
    /// </param>
    /// <returns>
    /// The <see cref="WhileCodeStatement"/> that was created. 
    /// </returns>
    public static ICodeStatementsHost AddLoopingPositiveLookAhead(
        this ICodeStatementsHost self,
        Group group,
        string match,
        Action<WhileCodeStatement> func)
    {
        var contents = group.State(Constants.States.ParsingContents, EType.CharacterCollection);
        var offset = group.State(Constants.States.ParsingOffset, EType.FileOffset);

        ICodeExpression expression = contents.Access(EProperty.CharacterCollectionLength)
            .GreaterThan(offset.Plus(new ValueExpression(match.Length)));
        for (var i = 0; i < match.Length; i++)
        {
            expression = expression.And(
                contents.ArrayAccess(offset.Plus(new ValueExpression(i)))
                    .Equal(new ValueExpression(match[i])));
        }

        return self.AddWhile(expression, func);
    }

    /// <summary>
    /// Allows to add a negative-lookahead to <paramref name="self"/>,
    /// checking whether <paramref name="match"/> can not be matched at this point.
    /// </summary>
    /// <param name="self">The container to add the lookahead to.</param>
    /// <param name="group">
    /// The <see cref="Group"/> that holds the <see cref="State"/> for
    /// <see cref="Constants.States.ParsingContents"/> and <see cref="Constants.States.ParsingOffset"/>.
    /// </param>
    /// <param name="match">
    /// The text to match against.
    /// </param>
    /// <param name="func">
    /// The function to call if <paramref name="match"/> is matched.
    /// </param>
    /// <returns>
    /// The <see cref="IfCodeStatement"/> that was created. 
    /// </returns>
    public static ICodeStatementsHost AddSingleNegativePositiveLookAhead(
        this ICodeStatementsHost self,
        Group group,
        string match,
        Action<IfCodeStatement> func)
    {
        var contents = group.State(Constants.States.ParsingContents, EType.CharacterCollection);
        var offset = group.State(Constants.States.ParsingOffset, EType.FileOffset);

        ICodeExpression expression = contents.Access(EProperty.CharacterCollectionLength)
            .GreaterThan(offset.Plus(new ValueExpression(match.Length)));
        for (var i = 0; i < match.Length; i++)
        {
            expression = expression.And(
                contents.ArrayAccess(offset.Plus(new ValueExpression(i)))
                    .Equal(new ValueExpression(match[i])));
        }

        return self.AddIf(expression.Not(), func);
    }

    /// <summary>
    /// Allows to add a negative-lookahead to <paramref name="self"/>,
    /// checking whether <paramref name="match"/> can not be matched at this point.
    /// </summary>
    /// <param name="self">The container to add the lookahead to.</param>
    /// <param name="group">
    /// The <see cref="Group"/> that holds the <see cref="State"/> for
    /// <see cref="Constants.States.ParsingContents"/> and <see cref="Constants.States.ParsingOffset"/>.
    /// </param>
    /// <param name="match">
    /// The text to match against.
    /// </param>
    /// <param name="func">
    /// The function to call if <paramref name="match"/> is matched.
    /// </param>
    /// <returns>
    /// The <see cref="WhileCodeStatement"/> that was created. 
    /// </returns>
    public static ICodeStatementsHost AddLoopingNegativePositiveLookAhead(
        this ICodeStatementsHost self,
        Group group,
        string match,
        Action<WhileCodeStatement> func)
    {
        var contents = group.State(Constants.States.ParsingContents, EType.CharacterCollection);
        var offset = group.State(Constants.States.ParsingOffset, EType.FileOffset);

        ICodeExpression expression = contents.Access(EProperty.CharacterCollectionLength)
            .GreaterThan(offset.Plus(new ValueExpression(match.Length)));
        for (var i = 0; i < match.Length; i++)
        {
            expression = expression.And(
                contents.ArrayAccess(offset.Plus(new ValueExpression(i)))
                    .Equal(new ValueExpression(match[i])));
        }

        return self.AddWhile(expression.Not(), func);
    }

    /// <summary>
    /// Progresses the parsing state by <paramref name="characters"/>.
    /// </summary>
    /// <param name="self"></param>
    /// <param name="group">
    /// The <see cref="Group"/> that holds the <see cref="State"/> for
    /// <see cref="Constants.States.ParsingContents"/>,
    /// <see cref="Constants.States.ParsingContentsLength"/>,
    /// <see cref="Constants.States.ParsingOffset"/>,
    /// <see cref="Constants.States.ParsingColumn"/> and
    /// <see cref="Constants.States.ParsingLine"/>.
    /// </param>
    /// <param name="characters">The amount of characters to consume.</param>
    /// <param name="defaultCase">
    /// Optionally the default case to call if no other case is matched.
    /// If not provided, default case will increase <see cref="Constants.States.ParsingLine"/> and
    /// <see cref="Constants.States.ParsingColumn"/>.
    /// </param>
    /// <returns></returns>
    public static ICodeStatementsHost ConsumeCharacters(
        this ICodeStatementsHost self,
        Group group,
        [ValueRange(1)] int characters,
        Action<CaseCodeStatement>? defaultCase = null)
        => ConsumeCharacters(self, group, new ValueExpression(characters), defaultCase);

    /// <summary>
    /// Progresses the parsing state by <paramref name="characters"/>.
    /// </summary>
    /// <param name="self"></param>
    /// <param name="group">
    /// The <see cref="Group"/> that holds the <see cref="State"/> for
    /// <see cref="Constants.States.ParsingContents"/>,
    /// <see cref="Constants.States.ParsingContentsLength"/>,
    /// <see cref="Constants.States.ParsingOffset"/>,
    /// <see cref="Constants.States.ParsingColumn"/> and
    /// <see cref="Constants.States.ParsingLine"/>.
    /// </param>
    /// <param name="characters">The amount of characters to consume as <see cref="ICodeExpression"/>.</param>
    /// <param name="defaultCase">
    /// Optionally the default case to call if no other case is matched.
    /// If not provided, default case will increase <see cref="Constants.States.ParsingLine"/> and
    /// <see cref="Constants.States.ParsingColumn"/>.
    /// </param>
    /// <returns></returns>
    public static ICodeStatementsHost ConsumeCharacters(
        this ICodeStatementsHost self,
        Group group,
        ICodeExpression characters,
        Action<CaseCodeStatement>? defaultCase = null)
    {
        var contents = group.State(Constants.States.ParsingContents, EType.CharacterCollection);
        var contentsLength = group.State(Constants.States.ParsingContentsLength, EType.Size);
        var offset = group.State(Constants.States.ParsingOffset, EType.FileOffset);
        var column = group.State(Constants.States.ParsingColumn, EType.FileOffset);
        var line = group.State(Constants.States.ParsingLine, EType.FileOffset);
        return self.AddFor(
            (forCodeStatement) => new VariableStatement(forCodeStatement, "i", EType.Integer, new ValueExpression(0)),
            (_, variable) => variable.LessThan(characters)
                .And(contentsLength.GreaterThan(contents.Access(EProperty.CharacterCollectionLength))),
            (_, variable) => variable.Increment(),
            (forCodeStatement, _) =>
                ConsumeSingleCharacter(defaultCase, forCodeStatement, contents, offset, column, line));
    }

    /// <summary>
    /// Progresses the parsing state by one.
    /// </summary>
    /// <param name="self"></param>
    /// <param name="group">
    /// The <see cref="Group"/> that holds the <see cref="State"/> for
    /// <see cref="Constants.States.ParsingContents"/>,
    /// <see cref="Constants.States.ParsingContentsLength"/>,
    /// <see cref="Constants.States.ParsingOffset"/>,
    /// <see cref="Constants.States.ParsingColumn"/> and
    /// <see cref="Constants.States.ParsingLine"/>.
    /// </param>
    /// <param name="defaultCase">
    /// Optionally the default case to call if no other case is matched.
    /// If not provided, default case will increase <see cref="Constants.States.ParsingLine"/> and
    /// <see cref="Constants.States.ParsingColumn"/>.
    /// </param>
    /// <returns></returns>
    public static ICodeStatementsHost ConsumeCharacter(
        this ICodeStatementsHost self,
        Group group,
        Action<CaseCodeStatement>? defaultCase = null)
    {
        var contents = group.State(Constants.States.ParsingContents, EType.CharacterCollection);
        var contentsLength = group.State(Constants.States.ParsingContentsLength, EType.Size);
        var offset = group.State(Constants.States.ParsingOffset, EType.FileOffset);
        var column = group.State(Constants.States.ParsingColumn, EType.FileOffset);
        var line = group.State(Constants.States.ParsingLine, EType.FileOffset);
        return self.AddIf(contentsLength.GreaterThan(contents.Access(EProperty.CharacterCollectionLength)),
            (ifCodeStatement) => ConsumeSingleCharacter(defaultCase, ifCodeStatement, contents, offset, column, line));
    }

    /// <summary>
    /// Creates an expression, representing the currently active character or '\0' if the end of the file is reached.
    /// </summary>
    /// <param name="group">
    /// The <see cref="Group"/> that holds the <see cref="State"/> for
    /// <see cref="Constants.States.ParsingContents"/>,
    /// <see cref="Constants.States.ParsingContentsLength"/>,
    /// <see cref="Constants.States.ParsingOffset"/>,
    /// </param>
    /// <param name="characterOffset">Allows to shift the "current" character by the given characters</param>
    /// <returns></returns>
    public static ConditionalExpression CurrentCharacter(
        this Group group,
        int characterOffset = 0)
    {
        var contents = group.State(Constants.States.ParsingContents, EType.CharacterCollection);
        var contentsLength = group.State(Constants.States.ParsingContentsLength, EType.Size);
        var offset = group.State(Constants.States.ParsingOffset, EType.FileOffset);

        switch (characterOffset)
        {
            case > 0:
                return new ConditionalExpression(
                    contentsLength.GreaterThanOrEqual(offset.Plus(new ValueExpression(characterOffset))),
                    new ValueExpression('\0'),
                    contents.ArrayAccess(offset.Plus(new ValueExpression(characterOffset))));
            case < 0:
                return new ConditionalExpression(
                    contentsLength.GreaterThanOrEqual(offset.Minus(new ValueExpression(-characterOffset)))
                        .And(offset.Minus(new ValueExpression(-characterOffset)).GreaterThanOrEqual(new ValueExpression(0))),
                    new ValueExpression('\0'),
                    contents.ArrayAccess(offset.Minus(new ValueExpression(-characterOffset))));
            case 0:
                return new ConditionalExpression(
                    contentsLength.GreaterThanOrEqual(offset),
                    new ValueExpression('\0'),
                    contents.ArrayAccess(offset));
        }
    }

    [SuppressMessage("ReSharper", "SuggestBaseTypeForParameter")]
    private static void ConsumeSingleCharacter(
        Action<CaseCodeStatement>? defaultCase,
        ICodeStatementsHost host,
        State contents,
        State offset,
        State column,
        State line)
    {
        var c = host.AddVariable(
            "c", EType.Character, contents.ArrayAccess(offset));
        host.AddSwitch(c.Ref(), (switchStatement) =>
        {
            switchStatement.AddCase(new[] {'\t', ' ', '\r'}, (caseStatement) =>
            {
                caseStatement.AddExpression(column.Increment());
                caseStatement.AddExpression(offset.Increment());
            });
            switchStatement.AddCase('\n', (caseStatement) =>
            {
                caseStatement.AddExpression(line.Increment());
                caseStatement.AddExpression(column.Assign(new ValueExpression(1)));
                caseStatement.AddExpression(offset.Increment());
            });
            if (defaultCase is not null)
                switchStatement.AddCaseDefault(defaultCase);
            else
                switchStatement.AddCaseDefault((caseStatement) =>
                {
                    caseStatement.AddExpression(column.Increment());
                    caseStatement.AddExpression(offset.Increment());
                });
        });
    }

    #endregion
}