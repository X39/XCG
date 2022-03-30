using System.IO;

namespace XCG.Generators.CSharp.CodeGeneration;

internal class WhilePart : ICSharpContainerBase
{
    private readonly string _condition;

    #region ISharpPart

    public WhilePart()
    {
        _condition = "true";
    }

    public WhilePart(string condition)
    {
        this._condition = condition;
    }

    public override void WriteImplementation(CSharpOptions options, StreamWriter writer, string whitespace)
    {
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