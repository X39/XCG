using System.Collections;

namespace XCG.Generators.Base;

public class WhileCodeStatement : CodeStatementHostBase
{
    public ICodeExpression Condition { get; }

    public WhileCodeStatement(ICodeStatementsHost parent, ICodeExpression condition) : base(parent)
    {
        Condition = condition;
    }
}
public class IfCodeStatement : CodeStatementHostBase
{
    public ICodeExpression Condition { get; }

    public IfCodeStatement(ICodeStatementsHost parent, ICodeExpression condition) : base(parent)
    {
        Condition = condition;
    }
}
public class ElseIfCodeStatement : CodeStatementHostBase
{
    public ICodeExpression Condition { get; }

    public ElseIfCodeStatement(ICodeStatementsHost parent, ICodeExpression condition) : base(parent)
    {
        Condition = condition;
    }
}
public class ElseCodeStatement : CodeStatementHostBase
{

    public ElseCodeStatement(ICodeStatementsHost parent) : base(parent)
    {
    }
}