using System;

namespace X39.Systems.XCG.Generators.Base.Extensions;

public static class StringExtensions
{
    public static string LowerTokenString(this string? str)
    {
        return str?.ToLowerInvariant() switch
        {
            "eof" => "\0",
            "eol" => "\n",
            null => throw new NullReferenceException("Failed to get value of token string"),
            _ => str,
        };
    }

    public static string LowerTokenString(this string? str, string defaultValue)
    {
        return (str?.ToLowerInvariant() ?? defaultValue) switch
        {
            "eof" => "\0",
            "eol" => "\n",
            _ => str ?? defaultValue,
        };
    }
}