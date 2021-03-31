using System.Collections.Generic;

namespace XCG.Parsing
{
    public interface IStatement
    {
        List<IStatement> Statements { get; }
    }
}