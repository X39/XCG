using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class Minus : IStatement
    {
        public bool Value { get; }

        public List<IStatement> Statements { get; }

        public Minus(params IStatement[] statements)
        {
            this.Statements = new List<IStatement>(statements);
        }
    }
}