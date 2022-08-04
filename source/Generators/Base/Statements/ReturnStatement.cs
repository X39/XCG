using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Statements;

public class ReturnStatement : ICodeStatement
{
    public ICodeExpression? ReturnValue { get; }
    public ICodeStatementsHost Parent { get; }

    public ReturnStatement(ICodeStatementsHost parent, ICodeExpression? value)
    {
        Parent = parent;
        ReturnValue = value;
    }
}