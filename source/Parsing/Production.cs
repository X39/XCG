using System;
using System.Collections.Generic;
using System.Text;

namespace XCG.Parsing
{
    public class Production : IStatement
    {
        public string Identifier { get; set; } = String.Empty;
        public List<IStatement> Children { get; set; } = new List<IStatement>();
        IEnumerable<IStatement> IStatement.Statements => Children;
        public Diagnostic Diagnostics { get; internal set; }
    }
}
