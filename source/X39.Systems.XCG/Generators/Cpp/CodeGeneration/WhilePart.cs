using System.IO;

namespace X39.Systems.XCG.Generators.Cpp.CodeGeneration;

internal class WhilePart : CppContainerBase
{
    private readonly EUsage _usage;
    private readonly string _condition;

    #region ICppPart

    public WhilePart(EUsage usage = EUsage.Implementation)
    {
        _condition = "true";
        this._usage = usage;
    }

    public WhilePart(string condition, EUsage usage = EUsage.Implementation)
    {
        this._condition = condition;
        this._usage = usage;
    }

    public override void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
    {
        if (!_usage.HasFlag(EUsage.Header)) return;
        writer.Write(whitespace);
        writer.Write("while (");
        writer.Write(_condition);
        writer.WriteLine(")");
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
        writer.Write("while (");
        writer.Write(_condition);
        writer.WriteLine(")");
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

    #endregion
}