using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;

namespace XCG.Generators.Base;

public static class CodeStatementHostExtensions
{
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

    public static ICodeStatementsHost AddPositiveLookAhead(
        this ICodeStatementsHost self,
        Group group,
        string match,
        Action<ICodeStatementsHost> func)
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

    #endregion
}