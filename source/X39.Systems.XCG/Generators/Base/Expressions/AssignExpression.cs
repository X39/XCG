﻿using X39.Systems.XCG.Generators.Base.Contracts;

namespace X39.Systems.XCG.Generators.Base.Expressions;

public class AssignExpression : ICodeExpression
{
    public ICodeExpression Target { get; }
    public ICodeExpression Value { get; }

    public AssignExpression(ICodeExpression target, ICodeExpression value)
    {
        Target = target;
        Value = value;
    }
}