using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class Plus : IStatement
    {
        public bool Value { get; }

        public List<IStatement> Statements { get; }

        public Plus(params IStatement[] statements)
        {
            this.Statements = new List<IStatement>(statements);
        }
    }
}