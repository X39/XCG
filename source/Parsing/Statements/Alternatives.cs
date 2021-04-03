using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Parsing.Statements
{
    public class Alternatives : IStatement
    {
        List<IStatement> IStatement.Statements => Matches.ToList<IStatement>();
        public List<Match> Matches { get; set; } = new List<Match>();
        public Diagnostic Diagnostics { get; internal set; }
    }
}
