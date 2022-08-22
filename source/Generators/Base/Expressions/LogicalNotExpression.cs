using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Expressions;

public class LogicalNotExpression : ICodeExpression
{
    public LogicalNotExpression(ICodeExpression expression)
    {
        Expression = expression;
    }

    public ICodeExpression Expression { get; }
}