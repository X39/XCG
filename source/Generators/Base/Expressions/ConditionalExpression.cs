using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Expressions;

public class ConditionalExpression : ICodeExpression
{
    public ICodeExpression Condition { get; }
    public ICodeExpression OnTrue { get; }
    public ICodeExpression OnFalse { get; }

    public ConditionalExpression(ICodeExpression condition, ICodeExpression onTrue, ICodeExpression onFalse)
    {
        Condition = condition;
        OnTrue = onTrue;
        OnFalse = onFalse;
    }
}