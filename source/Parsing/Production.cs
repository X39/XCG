using System.Collections.Generic;

namespace XCG.Parsing
{
    public class Production : IStatement, IHasDiagnostics
    {
        public string Identifier { get; set; } = string.Empty;
        public List<IStatement> Children { get; set; } = new();
        IEnumerable<IStatement> IStatement.Statements => Children;
        public Diagnostic Diagnostics { get; internal set; }
    }
}
