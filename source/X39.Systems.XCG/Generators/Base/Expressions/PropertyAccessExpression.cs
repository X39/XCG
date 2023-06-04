using X39.Systems.XCG.Generators.Base.Contracts;
using X39.Systems.XCG.Generators.Base.Enums;

namespace X39.Systems.XCG.Generators.Base.Expressions;

public class PropertyAccessExpression : ICodeExpression
{
    public PropertyAccessExpression(ICodeExpression source, EProperty property)
    {
        Source = source;
        Property = property;
    }

    public EProperty Property { get; }

    public ICodeExpression Source { get; }
}