using XCG.Generators.Base.Enums;

namespace XCG.Generators.Base.Parts;

public class Parameter
{
    public Function Function { get; }
    public EType Type { get; }
    public string Identifier { get; }

    public Parameter(Function function, EType type, string identifier)
    {
        Function = function;
        Type = type;
        Identifier = identifier;
    }
}