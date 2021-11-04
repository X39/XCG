using System;
using System.Collections.Generic;

namespace XCG.Parsing
{
    public struct CharacterRange : IStatement, IHasDiagnostics
    {
        public char Start { get; set; }
        public char End { get; set; }
        public Diagnostic Diagnostics { get; set; }

        IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();

        public CharacterRange(char start, char end, Diagnostic diagnostic)
        {
            Start = start;
            End = end;
            Diagnostics = diagnostic;
        }
        public override string ToString() => $@"range: `{Start}-{End}`";
    }
}