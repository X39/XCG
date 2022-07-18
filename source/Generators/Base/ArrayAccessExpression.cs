namespace XCG.Generators.Base;

public class ArrayAccessExpression : ICodeExpression
{
    public ICodeExpression Self { get; }
    public ICodeExpression Index { get; }

    public ArrayAccessExpression(ICodeExpression self, ICodeExpression index)
    {
        Self = self;
        Index = index;
    }
}