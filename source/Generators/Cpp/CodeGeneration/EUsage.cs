using System;

namespace XCG.Generators.Cpp.CodeGeneration;

[Flags]
public enum EUsage
{
    None = 0b00,
    Header = 0b01,
    Implementation = 0b10,
    All = Header | Implementation
}