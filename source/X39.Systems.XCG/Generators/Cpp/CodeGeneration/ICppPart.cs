using System.IO;

namespace X39.Systems.XCG.Generators.Cpp.CodeGeneration;

internal interface ICppPart
{
    string? BaseName { get; set; }
    void WriteHeader(CppOptions cppOptions, StreamWriter writer, string whitespace);
    void WriteImplementation(CppOptions cppOptions, StreamWriter writer, string whitespace);
}