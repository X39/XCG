using System.IO;

namespace XCG.Generators.Cpp
{
    internal interface ICppPart
    {
        string? BaseName { get; set; }
        void WriteHeader(CppOptions options, StreamWriter writer, string whitespace);
        void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace);
    }
}
