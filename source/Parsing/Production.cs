using System;
using System.Collections.Generic;
using System.Text;

namespace XCG.Parsing
{
    public class Production : IStatement
    {
        public string Identifier { get; set; } = String.Empty;
        public List<IStatement> Statements { get; set; } = new List<IStatement>();
        public Diagnostic Diagnostics { get; internal set; }
    }
}
