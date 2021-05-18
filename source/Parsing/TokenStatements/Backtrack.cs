﻿using System;
using System.Collections.Generic;

namespace XCG.Parsing.TokenStatements
{
    public class Backtrack : ITokenStatement
    {
        public Multiplicity Range { get; internal set; }
        public List<IStatement> Parts { get; internal set; } = new List<IStatement>();
        public bool Negated { get; set; }
        public Diagnostic Diagnostics { get; internal set; }
        IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
    }
}