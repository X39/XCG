using XCG.Generators.Base.Contracts;
using XCG.Generators.Base.Enums;
using XCG.Generators.Base.Expressions;
using XCG.Generators.Base.Parts;

namespace XCG.Generators.Base.Statements;

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