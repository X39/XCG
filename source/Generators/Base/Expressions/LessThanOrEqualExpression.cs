using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Expressions;

public class LessThanOrEqualExpression : ICodeExpression
{
    public ICodeExpression Left { get; }
    public ICodeExpression Right { get; }

    public LessThanOrEqualExpression(ICodeExpression left, ICodeExpression right)
    {
        Left = left;
        Right = right;
    }
}