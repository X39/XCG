using System;
using System.IO;

namespace XCG.Generators.CSharp.CodeGeneration;

internal class IfPart : ICSharpContainerBase
{
    public enum EIfScope
    {
        If,
        Else
    }

    private readonly EIfScope _ifScope;
    private readonly string? _condition;

    public IfPart(EIfScope ifScope, string? condition)
    {
        this._condition = condition;
        this._ifScope = ifScope;
    }

    public IfPart(bool isIf, string? condition)
    {
        this._condition = condition;
        _ifScope = isIf ? EIfScope.If : EIfScope.Else;
    }

    public override void WriteImplementation(CSharpOptions options, StreamWriter writer, string whitespace)
    {
        writer.Write(whitespace);
        switch (_ifScope)
        {
            case EIfScope.If:
                writer.WriteLine($@"if ({_condition})");
                break;
            case EIfScope.Else:
                writer.WriteLine(_condition is null ? $@"else" : $@"else if ({_condition})");

                break;
            default:
                throw new ArgumentOutOfRangeException();
        }

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