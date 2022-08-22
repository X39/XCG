using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Expressions;

public class IncreaseExpression : ICodeExpression
{
    public IncreaseExpression(ICodeExpression expression)
    {
        Expression = expression;
    }

    public ICodeExpression Expression { get; }
}