using XCG.Generators.Base.Contracts;
using XCG.Generators.Base.Enums;

namespace XCG.Generators.Base.Expressions;

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