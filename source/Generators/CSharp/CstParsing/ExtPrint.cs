﻿using System.Collections.Generic;

namespace XCG.Generators.CSharp.CstParsing;

internal static class ExtPrint
{
    public static IEnumerable<ICppPart> ToParts(this Parsing.Statements.Print print, CSharpOptions cSharpOptions)
    {
        if (print.Reference?.Referred is not Parsing.Message message)
        {
            throw new FatalException();
        }
        yield return new FullBody
        {
            $@"report(""{message.Text.Replace("\"", "\\\"")}"", {Constants.DepthVariable});"
        };
    }
}