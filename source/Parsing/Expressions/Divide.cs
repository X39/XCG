﻿using System.Collections.Generic;

namespace XCG.Parsing.Expressions;

public class Divide : IStatement, IHasDiagnostics
{
    public List<IStatement> Children { get; }
    IEnumerable<IStatement> IStatement.Statements => Children;
    public Diagnostic Diagnostics { get; internal init; }

    public Divide(params IStatement[] statements)
    {
        Children = new List<IStatement>(statements);
    }
}