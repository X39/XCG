using System.Collections.Generic;

namespace XCG.Parsing;

public interface IStatement
{
    IEnumerable<IStatement> Statements { get; }
}