using System.IO;

namespace XCG.Generators.CSharp.CodeGeneration;

public class ReturnPart : ICSharpPart
{
    public string? BaseName { get; set; }
    public EValueConstant Value { get; init; }
    public string? ValueString { get; init; }

    public ReturnPart()
    {
        Value = EValueConstant.None;
    }
    public ReturnPart(EValueConstant value)
    {
        Value = value;
    }
    public ReturnPart(string value)
    {
        ValueString = value;
    }

    public void WriteImplementation(CSharpOptions cSharpOptions, StreamWriter writer, string whitespace)
    {
        writer.Write(whitespace);
        if (!string.IsNullOrWhiteSpace(ValueString))
        {
            writer.Write("return ");
            writer.Write(ValueString);
        }
        else if (Value == EValueConstant.None)
        {
            writer.Write("return");
        }
        else
        {
            writer.Write("return ");
            writer.Write(Value.ToCppString());
        }
        writer.WriteLine(";");
    }
}