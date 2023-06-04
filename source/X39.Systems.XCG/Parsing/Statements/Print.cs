using System;
using System.Collections.Generic;

namespace X39.Systems.XCG.Parsing.Statements;

public class Print : IStatement, IHasDiagnostics
{
    public Reference? Reference { get; internal set; }
    public Diagnostic Diagnostics { get; internal init; }
    IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
}