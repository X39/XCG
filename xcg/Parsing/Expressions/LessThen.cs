using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class LessThen : IStatement
    {
        public bool Value { get; }

        public List<IStatement> Statements { get; }

        public LessThen(params IStatement[] statements)
        {
            this.Statements = new List<IStatement>(statements);
        }
    }
}