using System.Collections.Generic;

namespace XCG.Parsing.Statements
{
    public class Alternatives : IStatement, IHasDiagnostics
    {
        IEnumerable<IStatement> IStatement.Statements => Matches;
        public List<Match> Matches { get; set; } = new();
        public Diagnostic Diagnostics { get; internal set; }

        /// <summary>
        /// Indicates whether this <see cref="Alternatives"/> is supposed
        /// to handle error catching.
        /// </summary>
        public bool CatchesErrors { get; internal set; }
    }
}
