using System.IO;

namespace XCG.Generators.Cpp
{
    internal interface ICppPart
    {
        string? BaseName { get; set; }
        void WriteHeader(CppOptions cppOptions, StreamWriter writer, string whitespace);
        void WriteImplementation(CppOptions cppOptions, StreamWriter writer, string whitespace);
    }
}
