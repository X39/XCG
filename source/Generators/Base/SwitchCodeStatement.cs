namespace XCG.Generators.Base;

public class SwitchCodeStatement : CodeStatementHostBase
{
    public ICodeExpression SwitchOn { get; }

    public SwitchCodeStatement(ICodeStatementsHost parent, ICodeExpression switchOn) : base(parent)
    {
        SwitchOn = switchOn;
    }
}