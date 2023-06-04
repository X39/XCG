using X39.Systems.XCG.Generators.Base.Contracts;

namespace X39.Systems.XCG.Generators.Base.Statements;

public class SwitchCodeStatement : CodeStatementHostBase
{
    public ICodeExpression SwitchOn { get; }

    public SwitchCodeStatement(ICodeStatementsHost parent, ICodeExpression switchOn) : base(parent)
    {
        SwitchOn = switchOn;
    }
}