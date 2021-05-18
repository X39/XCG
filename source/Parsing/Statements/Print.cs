using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Parsing.Statements
{
    public class Print : IStatement
    {
        public Reference? Reference { get; internal set; }
        public Diagnostic Diagnostics { get; internal set; }
        IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
    }
}
