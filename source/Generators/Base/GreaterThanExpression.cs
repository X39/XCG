namespace XCG.Generators.Base;

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

public class EqualExpression : ICodeExpression
{
    public ICodeExpression Left { get; }
    public ICodeExpression Right { get; }

    public EqualExpression(ICodeExpression left, ICodeExpression right)
    {
        Left = left;
        Right = right;
    }
}