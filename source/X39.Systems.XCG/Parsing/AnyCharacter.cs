using System;
using System.Collections.Generic;

namespace X39.Systems.XCG.Parsing;

public struct AnyCharacter : IStatement, IHasDiagnostics
{
    public Diagnostic Diagnostics { get; internal init; }

    IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
    public override string ToString() => "any";
}