using System;
using System.Collections.Generic;

namespace XCG.Parsing
{
    public class LeftRecursive : IStatement
    {
        public string Identifier { get; set; } = String.Empty;
        public List<IStatement> Statements { get; set; } = new List<IStatement>();
        public Diagnostic Diagnostics { get; internal set; }
    }
}