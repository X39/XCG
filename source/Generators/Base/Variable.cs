namespace XCG.Generators.Base;

public class Variable
{
    public Function Function { get; }
    public EType Type { get; }
    public string Identifier { get; }

    public Variable(Function function, EType type, string identifier)
    {
        Function = function;
        Type = type;
        Identifier = identifier;
    }
}