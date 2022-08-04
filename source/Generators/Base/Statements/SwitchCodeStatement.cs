using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Statements;

public class SwitchCodeStatement : CodeStatementHostBase
{
    public ICodeExpression SwitchOn { get; }

    public SwitchCodeStatement(ICodeStatementsHost parent, ICodeExpression switchOn) : base(parent)
    {
        SwitchOn = switchOn;
    }
}