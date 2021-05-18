using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class NotEquivalentTo : IStatement
    {
        public List<IStatement> Children { get; }
        IEnumerable<IStatement> IStatement.Statements => Children;
        public Diagnostic Diagnostics { get; internal set; }

        public NotEquivalentTo(params IStatement[] statements)
        {
            this.Children = new List<IStatement>(statements);
        }
    }
}