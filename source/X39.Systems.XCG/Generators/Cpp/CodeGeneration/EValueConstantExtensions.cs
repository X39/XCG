using System;

namespace X39.Systems.XCG.Generators.Cpp.CodeGeneration;

internal static class EValueConstantExtensions
{
    internal static string ToCppString(this EValueConstant type) =>
        type switch
        {
            EValueConstant.None => string.Empty,
            EValueConstant.EmptyClosure => "{}",
            EValueConstant.True => "true",
            EValueConstant.False => "false",
            EValueConstant.NullChar => "'\\0'",
            _ => throw new NotImplementedException(),
        };
}