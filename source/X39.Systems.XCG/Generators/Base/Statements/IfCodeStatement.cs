using X39.Systems.XCG.Generators.Base.Contracts;

namespace X39.Systems.XCG.Generators.Base.Statements;

public class IfCodeStatement : CodeStatementHostBase
{
    public ICodeExpression Condition { get; }

    public IfCodeStatement(ICodeStatementsHost parent, ICodeExpression condition) : base(parent)
    {
        Condition = condition;
    }
}