using System.Linq.Expressions;
using X39.Systems.XCG.Generators.Base.Contracts;
using X39.Systems.XCG.Generators.Base.Meta;

namespace X39.Systems.XCG.Generators.Base.Statements;

public class WhileCodeStatement : CodeStatementHostBase, ILoopStatement
{
    public ICodeExpression Condition { get; }

    public WhileCodeStatement(ICodeStatementsHost parent, ICodeExpression condition) : base(parent)
    {
        Condition = condition;
    }
}