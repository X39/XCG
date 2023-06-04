using X39.Systems.XCG.Generators.Base.Contracts;

namespace X39.Systems.XCG.Generators.Base.Expressions;

public class PlusExpression : ICodeExpression
{
    public ICodeExpression Left { get; }
    public ICodeExpression Right { get; }

    public PlusExpression(ICodeExpression left, ICodeExpression right)
    {
        Left = left;
        Right = right;
    }
}