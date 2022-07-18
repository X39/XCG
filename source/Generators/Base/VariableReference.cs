namespace XCG.Generators.Base;

public class VariableReference : ICodeExpression
{
    public VariableStatement VariableStatement { get; }

    public VariableReference(VariableStatement self)
    {
        VariableStatement = self;
    }
}