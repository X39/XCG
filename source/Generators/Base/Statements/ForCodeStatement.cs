using System;
using XCG.Generators.Base.Contracts;
using XCG.Generators.Base.Enums;
using XCG.Generators.Base.Expressions;
using XCG.Generators.Base.Parts;

namespace XCG.Generators.Base.Statements;

public class ForCodeStatement : CodeStatementHostBase
{
    public ICodeExpression Condition { get; }
    public ICodeExpression Step { get; set; }
    public VariableStatement Variable { get; }

    public ForCodeStatement(ICodeStatementsHost parent,
        Func<ForCodeStatement, VariableStatement> variableFactory,
        Func<ForCodeStatement, VariableReference, ICodeExpression> conditionFactory,
        Func<ForCodeStatement, VariableReference, ICodeExpression> stepFactory) : base(parent)
    {
        Variable = variableFactory(this);
        Condition = conditionFactory(this, Variable.Ref());
        Step = stepFactory(this, Variable.Ref());
    }

}