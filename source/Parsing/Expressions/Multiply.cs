using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class Multiply : IStatement
    {
        public bool Value { get; }

        public List<IStatement> Statements { get; }
        public Diagnostic Diagnostics { get; internal set; }

        public Multiply(params IStatement[] statements)
        {
            this.Statements = new List<IStatement>(statements);
        }
    }
}