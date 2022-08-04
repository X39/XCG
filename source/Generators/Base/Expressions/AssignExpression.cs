using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Expressions;

public class AssignExpression : ICodeExpression
{
    public ICodeExpression Target { get; }
    public ICodeExpression Value { get; }

    public AssignExpression(ICodeExpression target, ICodeExpression value)
    {
        Target = target;
        Value = value;
    }
}