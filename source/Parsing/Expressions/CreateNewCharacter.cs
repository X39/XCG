using System;
using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    internal class CreateNewCharacter : IStatement, ICreateNew
    {
        IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
        public Diagnostic Diagnostics { get; set; }
    }
}