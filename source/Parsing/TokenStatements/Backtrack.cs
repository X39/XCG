using System.Collections.Generic;

namespace XCG.Parsing.TokenStatements
{
    public class Backtrack : ITokenStatement
    {
        public Multiplicity Range { get; internal set; }
        public List<IPart> Parts { get; internal set; } = new List<IPart>();
        public bool Negated { get; set; }
        public Diagnostic Diagnostics { get; internal set; }
    }
}