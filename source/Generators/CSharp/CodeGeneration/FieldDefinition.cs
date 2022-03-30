using System.IO;

namespace XCG.Generators.CSharp.CodeGeneration;

internal class FieldDefinition : ICSharpPart, IHasName
{
    public string? BaseName { get; set; }
    private ArgImpl Type { get; }
    public string Name => Type.Name;

    public FieldDefinition(ArgImpl typeImpl)
    {
        Type = typeImpl;
    }

    public void WriteHeader(CSharpOptions cSharpOptions, StreamWriter writer, string whitespace)
    {
        writer.Write(whitespace);
        writer.Write(Type.ToString(cSharpOptions));
        writer.WriteLine(";");
    }

    public void WriteImplementation(CSharpOptions cSharpOptions, StreamWriter writer, string whitespace)
    {
    }
}