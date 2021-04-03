using System;
using System.Collections.Generic;

namespace XCG.Validation
{
    internal class Rule : IRule
    {
        public string Realm { get; init; } = string.Empty;

        public int Code { get; init; }

        public ESeverity Severity { get; init; }

        public Func<Parsing.Parser, IEnumerable<Hint>> ValidationFunc { get; init; } = (parser) => Array.Empty<Hint>();

        public IEnumerable<Hint> IsValid(Parsing.Parser parser) => ValidationFunc(parser);
    }
}
