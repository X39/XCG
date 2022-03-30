using System.IO;

namespace XCG.Generators.CSharp.CodeGeneration;

internal interface ICSharpPart
{
    string? BaseName { get; set; }
    void WriteImplementation(CSharpOptions cSharpOptions, StreamWriter writer, string whitespace);
}