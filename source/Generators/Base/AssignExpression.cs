namespace XCG.Generators.Base;

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