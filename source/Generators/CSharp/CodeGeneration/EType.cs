using System;

namespace XCG.Generators.CSharp.CodeGeneration;

internal enum EType
{
    None,
    Void,
    Var,
    Boolean,
    Float,
    Double,
    Int32,
    Int64,
    String,
    StringView,
    SizeT,
    Char,
    OptionalBoolean,
    OptionalFloat,
    OptionalDouble,
    OptionalInt32,
    OptionalInt64,
    OptionalString,
    OptionalStringView,
    OptionalSizeT,
    OptionalChar,
    Token
}
internal static class ETypeExtensions
{
    internal static string ToCSharpString(this EType type, CSharpOptions cSharpOptions) =>
        type switch
        {
            EType.None => string.Empty,
            EType.Void => "void",
            EType.Var => "var",
            EType.Boolean => "bool",
            EType.Float => "float",
            EType.Double => "double",
            EType.Int32 => "int",
            EType.Int64 => "long",
            EType.String => "string",
            EType.StringView => "string",
            EType.SizeT => "int",
            EType.Char => "char",
            EType.OptionalBoolean => "bool?",
            EType.OptionalFloat => "float?",
            EType.OptionalDouble => "double?",
            EType.OptionalInt32 => "int?",
            EType.OptionalInt64 => "long?",
            EType.OptionalString => "string?",
            EType.OptionalSizeT => "int?",
            EType.OptionalChar => "char?",
            EType.Token => string.Concat(cSharpOptions.TypePrefix, cSharpOptions.TokenName),
            _ => throw new NotImplementedException(),
        };
}