using System;
using System.Collections.Generic;

namespace XCG.Parsing
{
    internal class EndOfFile : IStatement
    {
        IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
    }
}