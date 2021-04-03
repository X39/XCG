using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Parsing.Expressions
{
    public class CreateNewMap : IStatement
    {
        public List<IStatement> Statements { get; } = new List<IStatement>();
        public Diagnostic Diagnostics { get; internal set; }
    }
}
