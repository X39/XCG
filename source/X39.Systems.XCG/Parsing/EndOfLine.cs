using System;
using System.Collections.Generic;

namespace X39.Systems.XCG.Parsing;

internal class EndOfLine : IStatement
{
    IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
}