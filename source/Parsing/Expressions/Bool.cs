﻿using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class Bool : IStatement
    {
        public bool Value { get; }

        public List<IStatement> Statements { get; } = new List<IStatement>();
        public Diagnostic Diagnostics { get; internal set; }

        public Bool(bool v)
        {
            this.Value = v;
        }
    }
}