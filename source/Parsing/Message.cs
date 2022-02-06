using System;
using System.Collections.Generic;

namespace XCG.Parsing
{
    public class Message : IStatement, IHasDiagnostics
    {
        IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
        public string Identifier { get; set; }
        public string Text { get; internal set; }
        public ESeverity Severity { get; internal set; }
        public Diagnostic Diagnostics { get; internal init; }

        public Message()
        {
            Identifier = string.Empty;
            Text = string.Empty;
        }
    }
}