using XCG.Generators.Base.Contracts;
using XCG.Generators.Base.Statements;

namespace XCG.Generators.Base.Parts;

public class VariableReference : ICodeExpression
{
    public VariableStatement VariableStatement { get; }

    public VariableReference(VariableStatement self)
    {
        VariableStatement = self;
    }
}