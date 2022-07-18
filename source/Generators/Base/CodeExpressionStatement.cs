namespace XCG.Generators.Base;

public class CodeExpressionStatement : ICodeStatement
{
    public CodeExpressionStatement(ICodeStatementsHost parent, ICodeExpression expression)
    {
        Parent = parent;
        Expression = expression;
    }

    public ICodeExpression Expression { get; }
    public ICodeStatementsHost Parent { get; }
}