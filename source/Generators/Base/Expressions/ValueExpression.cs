using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Expressions;

public class ValueExpression : ICodeExpression
{
    public ValueExpression(object value)
    {
        Value = value;
    }

    public object Value { get; }
}