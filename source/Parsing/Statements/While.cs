using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Parsing.Statements
{
    public class While : IStatement
    {
        public IStatement? Condition { get; set; } = null;
        public List<IStatement> Statements { get; set; } = new List<IStatement>();
        public bool Negated { get; internal set; }
        public Diagnostic Diagnostics { get; internal set; }
    }
}
