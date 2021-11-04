using System.Collections.Generic;
using System.Linq;

namespace XCG.Parsing.Statements
{
    public class Match : IStatement, IHasDiagnostics
    {
        public List<IMatchPart> Matches { get; set; } = new();
        public List<IStatement> Children { get; set; } = new();
        IEnumerable<IStatement> IStatement.Statements => Matches.Concat(Children);
        public Diagnostic Diagnostics { get; internal set; }
    }
}
