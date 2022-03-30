using System.IO;

namespace XCG.Generators.CSharp.CodeGeneration;

internal class DebugPart : ICSharpContainerBase
{
    public DebugPart()
    {
    }

    public override void WriteImplementation(CSharpOptions options, StreamWriter writer, string whitespace)
    {
        foreach (var part in Parts)
        {
            part.BaseName = BaseName;
            part.WriteImplementation(options, writer, whitespace);
        }
    }
}