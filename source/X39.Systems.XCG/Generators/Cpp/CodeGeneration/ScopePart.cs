using System.IO;

namespace X39.Systems.XCG.Generators.Cpp.CodeGeneration;

internal class ScopePart : CppContainerBase
{
    private readonly EUsage _usage;

    public ScopePart(EUsage usage = EUsage.Implementation)
    {
        this._usage = usage;
    }

    public override void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
    {
        if (!_usage.HasFlag(EUsage.Header)) return;
        writer.Write(whitespace);
        writer.WriteLine("{");
        var subWhitespace = string.Concat("    ", whitespace);
        foreach (var part in Parts)
        {
            part.WriteHeader(options, writer, subWhitespace);
        }

        writer.Write(whitespace);
        writer.WriteLine("}");
    }

    public override void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace)
    {
        if (!_usage.HasFlag(EUsage.Implementation)) return;
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