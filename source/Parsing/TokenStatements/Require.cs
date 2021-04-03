using System.Collections.Generic;

namespace XCG.Parsing.TokenStatements
{
    public class Require : ITokenStatement
    {
        public Multiplicity Range { get; set; }
        public List<IPart> Parts { get; set; }
        public bool Negated { get; set; }
        public Diagnostic Diagnostics { get; internal set; }

        public Require()
        {
            this.Parts = new List<IPart>();
        }
    }
}