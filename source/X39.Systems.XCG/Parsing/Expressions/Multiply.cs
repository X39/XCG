﻿using System.Collections.Generic;

namespace X39.Systems.XCG.Parsing.Expressions;

public class Multiply : IStatement, IHasDiagnostics
{
    public List<IStatement> Children { get; }
    IEnumerable<IStatement> IStatement.Statements => Children;
    public Diagnostic Diagnostics { get; internal init; }

    public Multiply(params IStatement[] statements)
    {
        Children = new List<IStatement>(statements);
    }
}