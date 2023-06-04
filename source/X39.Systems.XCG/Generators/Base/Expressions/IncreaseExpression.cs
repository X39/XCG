using X39.Systems.XCG.Generators.Base.Contracts;

namespace X39.Systems.XCG.Generators.Base.Expressions;

public class IncreaseExpression : ICodeExpression
{
    public IncreaseExpression(ICodeExpression expression)
    {
        Expression = expression;
    }

    public ICodeExpression Expression { get; }
}