using System;
using System.Collections.Generic;

namespace X39.Systems.XCG.Parsing;

public class Comment : IStatement, IHasDiagnostics
{
    public string? Start { get; set; }
    public string? End { get; set; }
    IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
    public Diagnostic Diagnostics { get; internal init; }
}