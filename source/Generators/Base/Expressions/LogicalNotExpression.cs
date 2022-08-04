using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Expressions;

public class LogicalNotExpression : ICodeExpression
{
    public LogicalNotExpression(ICodeExpression self)
    {
        Self = self;
    }

    public ICodeExpression Self { get; }
}