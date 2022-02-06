using System.IO;

namespace XCG.Generators.Cpp.CodeGeneration;

public class ReturnPart : ICppPart
{
    public string? BaseName { get; set; }
    public EValueConstant Value { get; init; }
    public EUsage Usage { get; init; }
    public string? ValueString { get; init; }

    public ReturnPart(EUsage usage = EUsage.Implementation)
    {
        Value = EValueConstant.None;
        Usage = usage;
    }
    public ReturnPart(EValueConstant value, EUsage usage = EUsage.Implementation)
    {
        Value = value;
        Usage = usage;
    }
    public ReturnPart(string value, EUsage usage = EUsage.Implementation)
    {
        ValueString = value;
        Usage = usage;
    }
    public void WriteHeader(CppOptions cppOptions, StreamWriter writer, string whitespace)
    {
        if (Usage == EUsage.Header)
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

    public void WriteImplementation(CppOptions cppOptions, StreamWriter writer, string whitespace)
    {
        if (Usage == EUsage.Implementation)
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
}