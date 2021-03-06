using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class Or : IStatement
    {
        public bool Value { get; }

        public List<IStatement> Statements { get; }

        public Or(params IStatement[] statements)
        {
            this.Statements = new List<IStatement>(statements);
        }
    }
}