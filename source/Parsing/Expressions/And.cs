using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class And : IStatement
    {
        public bool Value { get; }

        public List<IStatement> Statements { get; }
        public Diagnostic Diagnostics { get; internal set; }

        public And(params IStatement[] statements)
        {
            this.Statements = new List<IStatement>(statements);
        }
    }
}