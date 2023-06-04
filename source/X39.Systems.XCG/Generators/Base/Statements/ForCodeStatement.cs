using System;
using X39.Systems.XCG.Generators.Base.Contracts;
using X39.Systems.XCG.Generators.Base.Parts;
using X39.Systems.XCG.Generators.Base.Enums;
using X39.Systems.XCG.Generators.Base.Expressions;

namespace X39.Systems.XCG.Generators.Base.Statements;

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