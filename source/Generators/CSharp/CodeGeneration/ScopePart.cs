using System.IO;

namespace XCG.Generators.CSharp.CodeGeneration;

internal class ScopePart : ICSharpContainerBase
{

    public ScopePart()
    {
    }

    public override void WriteImplementation(CSharpOptions options, StreamWriter writer, string whitespace)
    {
        writer.Write(whitespace);
        writer.WriteLine("{");
        var subWhitespace = string.Concat("    ", whitespace);
        foreach (var part in Parts)
        {
            part.WriteImplementation(options, writer, subWhitespace);
        }

        writer.Write(whitespace);
        writer.WriteLine("}");
    }
}