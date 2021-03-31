using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class LessThenOrEqualTo : IStatement
    {
        public bool Value { get; }

        public List<IStatement> Statements { get; }

        public LessThenOrEqualTo(params IStatement[] statements)
        {
            this.Statements = new List<IStatement>(statements);
        }
    }
}