using System.Collections.Generic;

namespace XCG.Generators.Cpp.Extensive
{
    internal static class ExtPrint
    {
        public static IEnumerable<ICppPart> ToParts(this Parsing.Statements.Print print, CppOptions cppOptions)
        {
            if (print.Reference.Refered is not Parsing.Message message)
            {
                throw new FatalException();
            }
            yield return new FullBody
            {
                $@"report(""{message.Text.Replace("\"", "\\\"")}"", {Constants.depthVariable});"
            };
        }
    }
}
