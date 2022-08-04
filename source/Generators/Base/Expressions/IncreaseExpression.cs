using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Expressions;

public class IncreaseExpression : ICodeExpression
{
    public IncreaseExpression(ICodeExpression self)
    {
        Self = self;
    }

    public ICodeExpression Self { get; }
}