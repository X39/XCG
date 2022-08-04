using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Expressions;

public class DecrementExpression : ICodeExpression
{
    public DecrementExpression(ICodeExpression self)
    {
        Self = self;
    }

    public ICodeExpression Self { get; }
}