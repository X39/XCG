using X39.Systems.XCG.Generators.Base.Contracts;
using X39.Systems.XCG.Generators.Base.Enums;

namespace X39.Systems.XCG.Generators.Base.Expressions;

public class EmptyValueExpression : ICodeExpression
{
    public EmptyValueExpression(EType type)
    {
        Type = type;
    }

    public EType Type { get; }
}