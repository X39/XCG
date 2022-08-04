using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Expressions;

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