using System;
using System.Collections.Generic;
using System.Text;

namespace XCG.Parsing
{
    public class Token
    {
        public string Identifier { get; set; } = String.Empty;
        public string Alias { get; set; } = String.Empty;
        public List<ITokenStatement> Statements { get; set; } = new List<ITokenStatement>();


        public override string ToString() => $@"{{ {nameof(Token)}: {(String.IsNullOrWhiteSpace(this.Alias) ? this.Identifier : this.Alias)}{(String.IsNullOrWhiteSpace(this.Alias) ? "" : $" ({this.Alias})")}}}";
    }
}
