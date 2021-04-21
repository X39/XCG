using System.Collections.Generic;

namespace XCG.Parsing
{
    internal class EOF : IStatement
    {
        public List<IStatement> Statements => new List<IStatement>();
    }
}