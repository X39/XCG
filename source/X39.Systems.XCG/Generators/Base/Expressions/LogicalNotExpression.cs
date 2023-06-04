using X39.Systems.XCG.Generators.Base.Contracts;

namespace X39.Systems.XCG.Generators.Base.Expressions;

public class LogicalNotExpression : ICodeExpression
{
    public LogicalNotExpression(ICodeExpression expression)
    {
        Expression = expression;
    }

    public ICodeExpression Expression { get; }
}