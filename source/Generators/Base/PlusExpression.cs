namespace XCG.Generators.Base;

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