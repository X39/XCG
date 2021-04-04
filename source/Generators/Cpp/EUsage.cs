using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Generators.Cpp
{
    [Flags]
    public enum EUsage
    {
        None = 0b00,
        Header = 0b01,
        Implementation = 0b10,
        All = Header | Implementation
    }
}
