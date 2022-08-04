using System.Linq.Expressions;
using XCG.Generators.Base.Contracts;
using XCG.Generators.Base.Meta;

namespace XCG.Generators.Base.Statements;

public class WhileCodeStatement : CodeStatementHostBase, ILoopStatement
{
    public ICodeExpression Condition { get; }

    public WhileCodeStatement(ICodeStatementsHost parent, ICodeExpression condition) : base(parent)
    {
        Condition = condition;
    }
}