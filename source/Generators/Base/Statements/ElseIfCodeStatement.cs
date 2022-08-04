using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Statements;

public class ElseIfCodeStatement : CodeStatementHostBase
{
    public ICodeExpression Condition { get; }

    public ElseIfCodeStatement(ICodeStatementsHost parent, ICodeExpression condition) : base(parent)
    {
        Condition = condition;
    }
}