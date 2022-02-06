using System.Collections.Generic;

namespace XCG.Parsing.Statements
{
    public class Set : IStatement, IHasDiagnostics
    {
        public List<IStatement> Children { get; set; } = new();
        public EActiveScope ActiveScope { get; set; }
        public EMode Mode { get; internal set; }
        public string Property { get; internal set; }
        public string Key { get; internal set; }
        public Diagnostic Diagnostics { get; internal init; }
        IEnumerable<IStatement> IStatement.Statements => Children;

        public Set()
        {
            Property = string.Empty;
            Key = string.Empty;
        }
    }
}
