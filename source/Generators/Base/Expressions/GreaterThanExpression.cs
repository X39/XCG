using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Expressions;

public class GreaterThanExpression : ICodeExpression
{
    public ICodeExpression Left { get; }
    public ICodeExpression Right { get; }

    public GreaterThanExpression(ICodeExpression left, ICodeExpression right)
    {
        Left = left;
        Right = right;
    }
}