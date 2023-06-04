using System;
using System.Collections.Generic;

namespace X39.Systems.XCG.Parsing.Expressions;

internal class CreateNewBoolean : IStatement, ICreateNew, IHasDiagnostics
{
    IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
    public Diagnostic Diagnostics { get; init; }
}