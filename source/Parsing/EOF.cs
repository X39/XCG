using System;
using System.Collections.Generic;

namespace XCG.Parsing
{
    internal class EOF : IStatement
    {
        IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
    }
}