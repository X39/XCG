using System;
using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class Bool : IStatement
    {
        public bool Value { get; }
        IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
        public Diagnostic Diagnostics { get; internal set; }

        public Bool(bool v)
        {
            this.Value = v;
        }
    }
}