using X39.Systems.XCG.Generators.Base.Contracts;
using X39.Systems.XCG.Generators.Base.Statements;

namespace X39.Systems.XCG.Generators.Base.Parts;

public class VariableReference : ICodeExpression
{
    public VariableStatement VariableStatement { get; }

    public VariableReference(VariableStatement self)
    {
        VariableStatement = self;
    }
}