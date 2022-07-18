namespace XCG.Generators.Base;

public class MinusExpression : ICodeExpression
{
    public ICodeExpression Left { get; }
    public ICodeExpression Right { get; }

    public MinusExpression(ICodeExpression left, ICodeExpression right)
    {
        Left = left;
        Right = right;
    }
}