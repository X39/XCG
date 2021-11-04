using System.Collections.Generic;

namespace XCG.Parsing
{
    public class Token : IStatement, IHasDiagnostics
    {
        public Diagnostic Diagnostics { get; set; }
        public string Identifier { get; set; } = string.Empty;
        public string Alias { get; set; } = string.Empty;
        public List<ITokenStatement> Children { get; set; } = new();
        IEnumerable<IStatement> IStatement.Statements => Children;


        public override string ToString() =>
            $@"{{ {nameof(Token)}: {(string.IsNullOrWhiteSpace(Alias) ? Identifier : Alias)}{(string.IsNullOrWhiteSpace(Alias) ? "" : $" ({Alias})")}}}";
    }
}