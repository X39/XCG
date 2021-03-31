using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class Divide : IStatement
    {
        public bool Value { get; }

        public List<IStatement> Statements { get; }

        public Divide(params IStatement[] statements)
        {
            this.Statements = new List<IStatement>(statements);
        }
    }
}