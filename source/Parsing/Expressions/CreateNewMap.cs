using System;
using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class CreateNewMap : IStatement, ICreateNew, IHasDiagnostics
    {
        IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
        public Diagnostic Diagnostics { get; internal init; }
    }
}
