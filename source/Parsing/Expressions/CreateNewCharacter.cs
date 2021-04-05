using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    internal class CreateNewCharacter : IStatement, ICreateNew
    {
        public List<IStatement> Statements { get; } = new List<IStatement>();
        public Diagnostic Diagnostics { get; set; }
    }
}