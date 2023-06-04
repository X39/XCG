using System;
using System.Collections.Generic;

namespace X39.Systems.XCG.Parsing.Expressions;

public class Bool : IStatement, IHasDiagnostics
{
    public bool Value { get; }
    IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
    public Diagnostic Diagnostics { get; internal init; }

    public Bool(bool v)
    {
        Value = v;
    }
}