using System.Linq.Expressions;
using X39.Util.Collections;

namespace XCG.Generators.Base;

public static class CodeExpressionExtensions
{
    public static LessThanExpression LessThan(this ICodeExpression self, ICodeExpression other)
    {
        return new LessThanExpression(self, other);
    }

    public static GreaterThanExpression GreaterThan(this ICodeExpression self, ICodeExpression other)
    {
        return new GreaterThanExpression(self, other);
    }

    public static EqualExpression Equal(this ICodeExpression self, ICodeExpression other)
    {
        return new EqualExpression(self, other);
    }

    public static OrExpression Or(this ICodeExpression self, ICodeExpression other)
    {
        return new OrExpression(self, other);
    }

    public static AndExpression And(this ICodeExpression self, ICodeExpression other)
    {
        return new AndExpression(self, other);
    }

    public static PlusExpression Plus(this ICodeExpression self, ICodeExpression other)
    {
        return new PlusExpression(self, other);
    }

    public static MinusExpression Minus(this ICodeExpression self, ICodeExpression other)
    {
        return new MinusExpression(self, other);
    }

    public static ArrayAccessExpression ArrayAccess(this ICodeExpression self, ICodeExpression index)
    {
        return new ArrayAccessExpression(self, index);
    }

    public static PropertyAccessExpression Access(this ICodeExpression self, EProperty property)
    {
        return new PropertyAccessExpression(self, property);
    }

    public static IncreaseExpression Increase(this ICodeExpression self)
    {
        return new IncreaseExpression(self);
    }

    public static AssignExpression Assign(this ICodeExpression self, ICodeExpression value)
    {
        return new AssignExpression(self, value);
    }

    public static AssignExpression Assign<T>(this ICodeExpression self, T value)
        where T : notnull
    {
        return new AssignExpression(self, new ValueExpression(value));
    }
}