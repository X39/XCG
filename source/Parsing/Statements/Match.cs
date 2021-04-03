using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Parsing.Statements
{
    public class Match : IStatement
    {
        public List<IMatchPart> Parts { get; set; } = new List<IMatchPart>();
        public List<IStatement> Statements { get; set; } = new List<IStatement>();
        public Diagnostic Diagnostics { get; internal set; }
    }
}
