using X39.Systems.XCG.Generators.Base.Contracts;

namespace X39.Systems.XCG.Generators.Base.Expressions;

public class ValueExpression : ICodeExpression
{
    public ValueExpression(object value)
    {
        Value = value;
    }

    public object Value { get; }
}