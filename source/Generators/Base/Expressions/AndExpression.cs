using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Expressions;

public class AndExpression : ICodeExpression
{
    public ICodeExpression Left { get; }
    public ICodeExpression Right { get; }

    public AndExpression(ICodeExpression left, ICodeExpression right)
    {
        Left = left;
        Right = right;
    }
}