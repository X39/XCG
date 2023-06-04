using System.Collections.Generic;
using System.IO;

namespace X39.Systems.XCG.Generators.Cpp.CodeGeneration;

internal class EnumDefinition : ICppPart, IHasName
{
    public string Name { get; }
    public string? BaseName { get; set; }
    private string FullName => BaseName is null ? Name : string.Concat(BaseName, "::", Name);

    public List<string> Entries { get; init; }

    public EnumDefinition(string name)
    {
        Entries = new List<string>();
        Name = name;
    }

    public void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
    {
        writer.Write(whitespace);
        writer.Write("enum class ");
        writer.WriteLine(FullName);

        writer.Write(whitespace);
        writer.WriteLine("{");

        var subWhitespace = whitespace + "    ";
        writer.Write(subWhitespace);
        writer.WriteLine("__UNSET__,");
        foreach (var entry in Entries)
        {
            writer.Write(subWhitespace);
            writer.Write(entry);
            writer.WriteLine(",");
        }

        writer.Write(subWhitespace);
        writer.WriteLine("__MAX__");

        writer.Write(whitespace);
        writer.WriteLine("};");
    }

    public void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace)
    {
    }
}