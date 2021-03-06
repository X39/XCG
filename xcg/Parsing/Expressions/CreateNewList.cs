using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Parsing.Expressions
{
    public class CreateNewList : IStatement
    {
        public List<IStatement> Statements { get; } = new List<IStatement>();
    }
}
