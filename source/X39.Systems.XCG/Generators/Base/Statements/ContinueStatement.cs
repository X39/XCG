using X39.Systems.XCG.Generators.Base.Contracts;

namespace X39.Systems.XCG.Generators.Base.Statements;

public class ContinueStatement : ICodeStatement
{
    public ContinueStatement(ICodeStatementsHost parent)
    {
        Parent = parent;
    }

    public ICodeStatementsHost Parent { get; }
}