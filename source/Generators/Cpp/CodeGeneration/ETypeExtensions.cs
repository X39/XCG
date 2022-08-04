using System;

namespace XCG.Generators.Cpp.CodeGeneration;

internal static class ETypeExtensions
{
    internal static string ToCppString(this EType type, CppOptions cppOptions) =>
        type switch
        {
            EType.None => string.Empty,
            EType.Void => "void",
            EType.Auto => "auto",
            EType.Boolean => "bool",
            EType.Float => "float",
            EType.Double => "double",
            EType.Int32 => "int",
            EType.Int64 => "long",
            EType.String => "std::string",
            EType.StringView => "std::string_view",
            EType.SizeT => "size_t",
            EType.Char => "char",
            EType.OptionalBoolean => "std::optional<bool>",
            EType.OptionalFloat => "std::optional<float>",
            EType.OptionalDouble => "std::optional<double>",
            EType.OptionalInt32 => "std::optional<int>",
            EType.OptionalInt64 => "std::optional<long>",
            EType.OptionalString => "std::optional<std::string>",
            EType.OptionalStringView => "std::optional<std::string_view>",
            EType.OptionalSizeT => "std::optional<size_t>",
            EType.OptionalChar => "std::optional<char>",
            EType.Token => string.Concat(cppOptions.TypePrefix, cppOptions.TokenName),
            _ => throw new NotImplementedException(),
        };
}