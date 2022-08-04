using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Statements;

public class ContinueStatement : ICodeStatement
{
    public ContinueStatement(ICodeStatementsHost parent)
    {
        Parent = parent;
    }

    public ICodeStatementsHost Parent { get; }
}