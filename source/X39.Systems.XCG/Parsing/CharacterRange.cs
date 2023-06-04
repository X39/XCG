using System;
using System.Collections.Generic;

namespace X39.Systems.XCG.Parsing;

public readonly record struct CharacterRange : IStatement, IHasDiagnostics
{
    public char Start { get; }
    public char End { get; }
    public Diagnostic Diagnostics { get; }

    IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();

    public CharacterRange(char start, char end, Diagnostic diagnostic)
    {
        Start = start;
        End = end;
        Diagnostics = diagnostic;
    }
    public override string ToString() => $@"range: `{Start}-{End}`";
}