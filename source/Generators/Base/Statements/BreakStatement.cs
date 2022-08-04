using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Statements;

public class BreakStatement : ICodeStatement
{
    public BreakStatement(ICodeStatementsHost parent)
    {
        Parent = parent;
    }

    public ICodeStatementsHost Parent { get; }
}