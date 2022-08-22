using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Expressions;

public class DecrementExpression : ICodeExpression
{
    public DecrementExpression(ICodeExpression expression)
    {
        Expression = expression;
    }

    public ICodeExpression Expression { get; }
}