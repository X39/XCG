using System;
using System.Collections.Generic;

namespace XCG.Parsing.Expressions
{
    public class Number : IStatement, IHasDiagnostics
    {
        public double Value { get; }
        IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
        public Diagnostic Diagnostics { get; internal init; }
        public Number(double number)
        {
            Value = number;
        }
    }
}
