using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class LessThen : IStatement
    {
        public bool Value { get; }

        public List<IStatement> Statements { get; }
        public Diagnostic Diagnostics { get; internal set; }

        public LessThen(params IStatement[] statements)
        {
            this.Statements = new List<IStatement>(statements);
        }
    }
}