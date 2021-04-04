using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    internal class CreateNewBoolean : IStatement, ICreateNew
    {
        public List<IStatement> Statements { get; } = new List<IStatement>();
        public Diagnostic Diagnostics { get; set; }
    }
}