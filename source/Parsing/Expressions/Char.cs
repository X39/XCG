using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class Char : IStatement
    {
        public char Value { get; }

        public List<IStatement> Statements { get; } = new List<IStatement>();
        public Diagnostic Diagnostics { get; internal set; }

        public Char(char v)
        {
            this.Value = v;
        }
    }
}