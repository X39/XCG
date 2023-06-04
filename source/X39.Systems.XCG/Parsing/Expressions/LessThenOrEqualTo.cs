using System.Collections.Generic;

namespace X39.Systems.XCG.Parsing.Expressions;

public class LessThenOrEqualTo : IStatement, IHasDiagnostics
{
    public List<IStatement> Children { get; }
    IEnumerable<IStatement> IStatement.Statements => Children;
    public Diagnostic Diagnostics { get; internal init; }

    public LessThenOrEqualTo(params IStatement[] statements)
    {
        Children = new List<IStatement>(statements);
    }
}