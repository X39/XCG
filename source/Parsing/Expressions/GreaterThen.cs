using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class GreaterThen : IStatement, IHasDiagnostics
    {
        public List<IStatement> Children { get; }
        IEnumerable<IStatement> IStatement.Statements => Children;
        public Diagnostic Diagnostics { get; internal set; }

        public GreaterThen(params IStatement[] statements)
        {
            Children = new List<IStatement>(statements);
        }
    }
}