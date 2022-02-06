using System.Collections.Generic;

namespace XCG.Parsing.Expressions;

public class And : IStatement, IHasDiagnostics
{
    public List<IStatement> Children { get; }
    IEnumerable<IStatement> IStatement.Statements => Children;
    public Diagnostic Diagnostics { get; internal init; }

    public And(params IStatement[] statements)
    {
        Children = new List<IStatement>(statements);
    }
}