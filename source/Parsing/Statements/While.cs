using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Parsing.Statements
{
    public class While : IStatement
    {
        public List<IStatement> Condition { get; set; } = new List<IStatement>();
        public List<IStatement> Statements { get; set; } = new List<IStatement>();
        public bool Negated { get; internal set; }
        public Diagnostic Diagnostics { get; internal set; }
    }
}
