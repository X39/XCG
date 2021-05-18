﻿using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class LessThen : IStatement
    {
        public List<IStatement> Children { get; }
        IEnumerable<IStatement> IStatement.Statements => Children;
        public Diagnostic Diagnostics { get; internal set; }

        public LessThen(params IStatement[] statements)
        {
            this.Children = new List<IStatement>(statements);
        }
    }
}