using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Parsing.Expressions
{
    public class Number : IStatement
    {
        public Number(double number)
        {
            this.Value = number;
        }

        public List<IStatement> Statements { get; } = new List<IStatement>();
        public double Value { get; }
        public Diagnostic Diagnostics { get; internal set; }
    }
}
