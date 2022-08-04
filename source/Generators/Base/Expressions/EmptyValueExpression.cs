using XCG.Generators.Base.Contracts;
using XCG.Generators.Base.Enums;

namespace XCG.Generators.Base.Expressions;

public class EmptyValueExpression : ICodeExpression
{
    public EmptyValueExpression(EType type)
    {
        Type = type;
    }

    public EType Type { get; }
}