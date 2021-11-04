using System;
using System.Collections.Generic;

namespace XCG.Parsing
{
    public struct AnyCharacter : IStatement, IHasDiagnostics
    {
        public Diagnostic Diagnostics { get; internal set; }

        IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
        public override string ToString() => "any";
    }
}