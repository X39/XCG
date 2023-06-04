using X39.Systems.XCG.Generators.Base.Contracts;
using X39.Systems.XCG.Generators.Base.Enums;
using X39.Systems.XCG.Generators.Base.Parts;
using X39.Systems.XCG.Generators.Base.Expressions;

namespace X39.Systems.XCG.Generators.Base.Statements;

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