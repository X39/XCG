using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Expressions;

public class ArrayAccessExpression : ICodeExpression
{
    public ICodeExpression Expression { get; }
    public ICodeExpression Index { get; }

    public ArrayAccessExpression(ICodeExpression expression, ICodeExpression index)
    {
        Expression = expression;
        Index = index;
    }
}