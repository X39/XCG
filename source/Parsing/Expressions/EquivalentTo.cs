﻿
using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class EquivalentTo : IStatement
    {
        public bool Value { get; }

        public List<IStatement> Statements { get; }

        public EquivalentTo(params IStatement[] statements)
        {
            this.Statements = new List<IStatement>(statements);
        }
    }
}