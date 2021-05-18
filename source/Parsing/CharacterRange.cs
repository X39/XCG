using System;
using System.Collections.Generic;

namespace XCG.Parsing
{
    public struct CharacterRange : IStatement
    {
        public char Start { get; set; }
        public char End { get; set; }
        public Diagnostic Diagnostics { get; set; }

        IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();

        public CharacterRange(char start, char end, Diagnostic diagnostic)
        {
            this.Start = start;
            this.End = end;
            this.Diagnostics = diagnostic;
        }
        public override string ToString() => $@"range: `{this.Start}-{this.End}`";
    }
}