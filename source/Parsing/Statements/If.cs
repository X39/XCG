using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Parsing.Statements
{
    public class If : IStatement
    {
        public IStatement? Condition { get; set; } = null;
        public List<IStatement> Children { get; set; } = new List<IStatement>();
        public List<IStatement> Else { get; set; } = new List<IStatement>();
        public bool Negated { get; internal set; }
        public Diagnostic Diagnostics { get; internal set; }
        IEnumerable<IStatement> IStatement.Statements => Condition is null ? Children.Concat(Else) : Children.Concat(Else).Prepend(Condition);
    }
}
