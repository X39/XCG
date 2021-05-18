using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Parsing.Expressions
{
    public class CreateNewMap : IStatement, ICreateNew
    {
        IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
        public Diagnostic Diagnostics { get; internal set; }
    }
}
