using X39.Systems.XCG.Generators.Base.Contracts;
using X39.Systems.XCG.Generators.Base.Enums;

namespace X39.Systems.XCG.Generators.Base.Parts;

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