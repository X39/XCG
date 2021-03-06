using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class GreaterThenOrEqualTo : IStatement
    {
        public bool Value { get; }

        public List<IStatement> Statements { get; }

        public GreaterThenOrEqualTo(params IStatement[] statements)
        {
            this.Statements = new List<IStatement>(statements);
        }
    }
}