using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Expressions;

public class GreaterThanOrEqualExpression : ICodeExpression
{
    public ICodeExpression Left { get; }
    public ICodeExpression Right { get; }

    public GreaterThanOrEqualExpression(ICodeExpression left, ICodeExpression right)
    {
        Left = left;
        Right = right;
    }
}