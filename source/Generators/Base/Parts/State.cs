using XCG.Generators.Base.Contracts;
using XCG.Generators.Base.Enums;

namespace XCG.Generators.Base.Parts;

public class State : ICodeExpression
{
    public string Identifier { get; }
    public EType Type { get; }

    public State(string identifier, EType type)
    {
        Identifier = identifier;
        Type = type;
    }
}