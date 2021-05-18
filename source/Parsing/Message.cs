using System;
using System.Collections.Generic;

namespace XCG.Parsing
{
    public class Message : IStatement
    {
        IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
        public string Identifier { get; set; }
        public string Text { get; internal set; }
        public ESeverity Severity { get; internal set; }
        public Diagnostic Diagnostics { get; internal set; }

        public Message()
        {
            this.Identifier = string.Empty;
            this.Text = string.Empty;
        }
    }
}