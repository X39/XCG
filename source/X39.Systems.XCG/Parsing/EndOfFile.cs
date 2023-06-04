using System;
using System.Collections.Generic;

namespace X39.Systems.XCG.Parsing;

internal class EndOfFile : IStatement
{
    IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
}