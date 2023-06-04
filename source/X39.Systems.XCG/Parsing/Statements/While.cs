using System.Collections.Generic;
using System.Linq;

namespace X39.Systems.XCG.Parsing.Statements;

public class While : IStatement, IHasDiagnostics
{
    public IStatement? Condition { get; set; } = null;
    public List<IStatement> Children { get; set; } = new();
    public bool Negated { get; internal set; }
    public Diagnostic Diagnostics { get; internal init; }
    IEnumerable<IStatement> IStatement.Statements => Condition is null ? Children : Children.Prepend(Condition);
}