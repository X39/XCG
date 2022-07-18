using System;

namespace XCG.Generators.Base;

public class ValueExpression : ICodeExpression
{
    public ValueExpression(object value)
    {
        Value = value;
    }

    public object Value { get; }
}