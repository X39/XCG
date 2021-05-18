using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Parsing.Statements
{
    public class Get : IStatement
    {
        public List<IStatement> Children { get; set; } = new List<IStatement>();
        public EActiveScope ActiveScope { get; set; }
        public EMode Mode { get; internal set; }
        public string Property { get; internal set; }
        public string Key { get; internal set; }
        public Diagnostic Diagnostics { get; internal set; }
        IEnumerable<IStatement> IStatement.Statements => Children;

        public Get()
        {
            this.Property = string.Empty;
            this.Key = string.Empty;
        }
    }
}
