using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class Character : IStatement
    {
        public char Value { get; }

        public List<IStatement> Statements { get; } = new List<IStatement>();
        public Diagnostic Diagnostics { get; internal set; }

        public Character(char v)
        {
            this.Value = v;
        }
    }
}