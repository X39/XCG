using X39.Systems.XCG.Generators.Base.Contracts;
using X39.Systems.XCG.Generators.Base.Enums;
using X39.Systems.XCG.Generators.Base.Expressions;

namespace X39.Systems.XCG.Generators.Base.Extensions;

public static class CodeExpressionExtensions
{
    public static ConditionalExpression Conditional(this ICodeExpression condition, ICodeExpression onTrue, ICodeExpression onFalse)
    {
        return new ConditionalExpression(condition, onTrue, onFalse);
    }
    public static LessThanOrEqualExpression LessThanOrEqual(this ICodeExpression self, ICodeExpression other)
    {
        return new LessThanOrEqualExpression(self, other);
    }
    public static LessThanExpression LessThan(this ICodeExpression self, ICodeExpression other)
    {
        return new LessThanExpression(self, other);
    }

    public static GreaterThanExpression GreaterThan(this ICodeExpression self, ICodeExpression other)
    {
        return new GreaterThanExpression(self, other);
    }
    
    public static GreaterThanOrEqualExpression GreaterThanOrEqual(this ICodeExpression self, ICodeExpression other)
    {
        return new GreaterThanOrEqualExpression(self, other);
    }

    public static LogicalNotExpression Not(this ICodeExpression self)
    {
        return new LogicalNotExpression(self);
    }

    public static EqualExpression Equal(this ICodeExpression self, ICodeExpression other)
    {
        return new EqualExpression(self, other);
    }

    public static NotEqualExpression NotEqual(this ICodeExpression self, ICodeExpression other)
    {
        return new NotEqualExpression(self, other);
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

    public static IncreaseExpression Increment(this ICodeExpression self)
    {
        return new IncreaseExpression(self);
    }


    public static DecrementExpression Decrement(this ICodeExpression self)
    {
        return new DecrementExpression(self);
    }

    public static AssignExpression Assign(this ICodeExpression self, ICodeExpression value)
    {
        return new AssignExpression(self, value);
    }
}