using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Parsing.Statements
{
    public class Set : IStatement
    {
        public List<IStatement> Statements { get; set; } = new List<IStatement>();
        public EActiveScope ActiveScope { get; set; }
        public EMode Mode { get; internal set; }
        public string Property { get; internal set; }
        public string Key { get; internal set; }
    }
}
