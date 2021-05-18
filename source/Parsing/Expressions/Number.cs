using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Parsing.Expressions
{
    public class Number : IStatement
    {
        public double Value { get; }
        IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();
        public Diagnostic Diagnostics { get; internal set; }
        public Number(double number)
        {
            this.Value = number;
        }
    }
}
