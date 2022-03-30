using System;

namespace XCG.Generators.CSharp.CodeGeneration;

public enum EValueConstant
{
    None,
    EmptyClosure,
    True,
    False,
    NullChar,
}
internal static class EValueConstantExtensions
{
    internal static string ToCppString(this EValueConstant type) =>
        type switch
        {
            EValueConstant.None => string.Empty,
            EValueConstant.EmptyClosure => "default",
            EValueConstant.True => "true",
            EValueConstant.False => "false",
            EValueConstant.NullChar => "'\\0'",
            _ => throw new NotImplementedException(),
        };
}