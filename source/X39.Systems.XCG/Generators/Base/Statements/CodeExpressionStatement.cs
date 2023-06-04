using X39.Systems.XCG.Generators.Base.Contracts;

namespace X39.Systems.XCG.Generators.Base.Statements;

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