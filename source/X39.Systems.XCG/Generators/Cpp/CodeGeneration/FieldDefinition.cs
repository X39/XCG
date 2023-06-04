using System.IO;

namespace X39.Systems.XCG.Generators.Cpp.CodeGeneration;

internal class FieldDefinition : ICppPart, IHasName
{
    public string? BaseName { get; set; }
    private ArgImpl Type { get; }
    public string Name => Type.Name;

    public FieldDefinition(ArgImpl typeImpl)
    {
        Type = typeImpl;
    }

    public void WriteHeader(CppOptions cppOptions, StreamWriter writer, string whitespace)
    {
        writer.Write(whitespace);
        writer.Write(Type.ToString(cppOptions));
        writer.WriteLine(";");
    }

    public void WriteImplementation(CppOptions cppOptions, StreamWriter writer, string whitespace)
    {
    }
}