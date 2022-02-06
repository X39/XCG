using System.Collections.Generic;

namespace XCG.Parsing.Expressions;

public class NotEquivalentTo : IStatement, IHasDiagnostics
{
    public List<IStatement> Children { get; }
    IEnumerable<IStatement> IStatement.Statements => Children;
    public Diagnostic Diagnostics { get; internal init; }

    public NotEquivalentTo(params IStatement[] statements)
    {
        Children = new List<IStatement>(statements);
    }
}