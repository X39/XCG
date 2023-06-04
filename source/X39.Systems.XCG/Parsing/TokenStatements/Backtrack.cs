using System;
using System.Collections.Generic;

namespace X39.Systems.XCG.Parsing.TokenStatements;

public class Backtrack : ITokenStatement, IHasDiagnostics
{
    public Multiplicity Range { get; internal set; }
    public List<IStatement> Parts { get; internal set; } = new();
    public bool Negated { get; set; }
    public Diagnostic Diagnostics { get; internal init; }
    IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
}