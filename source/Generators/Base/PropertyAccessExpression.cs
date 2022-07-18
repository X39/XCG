namespace XCG.Generators.Base;

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