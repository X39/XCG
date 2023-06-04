using X39.Systems.XCG.Generators.Base.Contracts;

namespace X39.Systems.XCG.Generators.Base.Expressions;

public class NotEqualExpression : ICodeExpression
{
    public ICodeExpression Left { get; }
    public ICodeExpression Right { get; }

    public NotEqualExpression(ICodeExpression left, ICodeExpression right)
    {
        Left = left;
        Right = right;
    }
}