﻿namespace X39.Systems.XCG.Generators.Cpp.CstParsing;

public static class ExtChar
{
    public static string Escape(this char c)
    {
        return c switch
        {
            '\'' => "\\'",
            '\"' => "\\\"",
            '?' => "\\?",
            '\\' => "\\\\",
            '\a' => "\\a",
            '\b' => "\\b",
            '\f' => "\\f",
            '\n' => "\\n",
            '\r' => "\\r",
            '\t' => "\\t",
            '\v' => "\\v",
            '\0' => "\\0",
            _ => c.ToString()
        };
    }
}