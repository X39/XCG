using X39.Systems.XCG.Generators.Base.Contracts;

namespace X39.Systems.XCG.Generators.Base.Expressions;

public class DecrementExpression : ICodeExpression
{
    public DecrementExpression(ICodeExpression expression)
    {
        Expression = expression;
    }

    public ICodeExpression Expression { get; }
}