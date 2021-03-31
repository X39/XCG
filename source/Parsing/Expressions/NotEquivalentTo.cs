using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class NotEquivalentTo : IStatement
    {
        public bool Value { get; }

        public List<IStatement> Statements { get; }

        public NotEquivalentTo(params IStatement[] statements)
        {
            this.Statements = new List<IStatement>(statements);
        }
    }
}