using System;
using System.Collections.Generic;

namespace XCG.Parsing
{
    internal class EndOfLine : IStatement
    {
        IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
    }
}