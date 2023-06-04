using System.Collections.Generic;

namespace X39.Systems.XCG.Parsing;

public interface IStatement
{
    IEnumerable<IStatement> Statements { get; }
}