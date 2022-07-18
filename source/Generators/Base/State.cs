namespace XCG.Generators.Base;

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