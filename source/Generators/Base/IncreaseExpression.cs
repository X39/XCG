namespace XCG.Generators.Base;

public class IncreaseExpression : ICodeExpression
{
    public IncreaseExpression(ICodeExpression self)
    {
        Self = self;
    }

    public ICodeExpression Self { get; }
}