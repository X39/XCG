using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Expressions;

public class OrExpression : ICodeExpression
{
    public ICodeExpression Left { get; }
    public ICodeExpression Right { get; }

    public OrExpression(ICodeExpression left, ICodeExpression right)
    {
        Left = left;
        Right = right;
    }
}