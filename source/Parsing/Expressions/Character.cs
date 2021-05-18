using System;
using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class Character : IStatement
    {
        public char Value { get; }
        IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
        public Diagnostic Diagnostics { get; internal set; }

        public Character(char v)
        {
            this.Value = v;
        }
    }
}