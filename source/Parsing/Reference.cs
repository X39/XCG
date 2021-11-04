using System;
using System.Collections.Generic;

namespace XCG.Parsing
{
    public class Reference : IMatchPart, IStatement, IHasDiagnostics
    {
        public IStatement? Refered { get; set; }
        public string Text { get; set; }
        public bool IsOptional { get; set; }
        public bool IsCaptured { get; set; }
        public bool IsAlias { get; set; }
        public string? CaptureName { get; set; }
        public Diagnostic Diagnostics { get; internal set; }
        IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();

        public Reference(string text)
        {
            this.Refered = null;
            this.Text = text;
        }

        public override string ToString()
        {
            return $@"$ref: {this.Text} ({this.Refered?.ToString() ?? "NULL"})";
        }
    }
}
