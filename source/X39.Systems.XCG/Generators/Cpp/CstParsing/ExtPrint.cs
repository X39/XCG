using System.Collections.Generic;
using X39.Systems.XCG.Generators.Cpp.CodeGeneration;

namespace X39.Systems.XCG.Generators.Cpp.CstParsing;

internal static class ExtPrint
{
    public static IEnumerable<ICppPart> ToParts(this Parsing.Statements.Print print, CppOptions cppOptions)
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