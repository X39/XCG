using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Statements;

public class IfCodeStatement : CodeStatementHostBase
{
    public ICodeExpression Condition { get; }

    public IfCodeStatement(ICodeStatementsHost parent, ICodeExpression condition) : base(parent)
    {
        Condition = condition;
    }
}