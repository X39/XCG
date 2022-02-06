﻿
using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class EquivalentTo : IStatement, IHasDiagnostics
    {
        public List<IStatement> Children { get; }
        IEnumerable<IStatement> IStatement.Statements => Children;
        public Diagnostic Diagnostics { get; internal init; }

        public EquivalentTo(params IStatement[] statements)
        {
            Children = new List<IStatement>(statements);
        }
    }
}