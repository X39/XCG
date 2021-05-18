using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Parsing.Statements
{
    public class Match : IStatement
    {
        public List<IMatchPart> Matches { get; set; } = new List<IMatchPart>();
        public List<IStatement> Children { get; set; } = new List<IStatement>();
        IEnumerable<IStatement> IStatement.Statements => Matches.Concat(Children);
        public Diagnostic Diagnostics { get; internal set; }
    }
}
