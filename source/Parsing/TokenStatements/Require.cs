using System;
using System.Collections.Generic;

namespace XCG.Parsing.TokenStatements
{
    public class Require : ITokenStatement
    {
        public Multiplicity Range { get; set; }
        public List<IStatement> Parts { get; set; }
        public bool Negated { get; set; }
        public Diagnostic Diagnostics { get; internal set; }
        IEnumerable<IStatement> IStatement.Statements => Parts;

        public Require()
        {
            this.Parts = new List<IStatement>();
        }
    }
}