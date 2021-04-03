using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Parsing.Statements
{
    public class Print : IStatement
    {
        public List<IStatement> Statements { get; set; } = new List<IStatement>();
        public Reference Reference { get; internal set; }
        public Diagnostic Diagnostics { get; internal set; }
    }
}
