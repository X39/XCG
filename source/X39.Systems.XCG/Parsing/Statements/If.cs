using System.Collections.Generic;
using System.Linq;

namespace X39.Systems.XCG.Parsing.Statements;

public class If : IStatement, IHasDiagnostics
{
    public IStatement? Condition { get; set; } = null;
    public List<IStatement> Children { get; set; } = new();
    public List<IStatement> Else { get; set; } = new();
    public bool Negated { get; internal set; }
    public Diagnostic Diagnostics { get; internal init; }
    IEnumerable<IStatement> IStatement.Statements => Condition is null ? Children.Concat(Else) : Children.Concat(Else).Prepend(Condition);
}