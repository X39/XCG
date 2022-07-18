namespace XCG.Generators.Base;

public class VariableStatement : ICodeStatement
{
    public string Identifier { get; }
    public EType Type { get; }
    public ICodeExpression InitialValue { get; }

    public VariableStatement(ICodeStatementsHost parent, string identifier, EType type, ICodeExpression initialValue)
    {
        Identifier = identifier;
        Type = type;
        InitialValue = initialValue;
        Parent = parent;
    }
    
    public VariableReference Ref()
    {
        return new VariableReference(this);
    }

    public ICodeStatementsHost Parent { get; }
}