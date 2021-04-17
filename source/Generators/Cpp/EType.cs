﻿using System;

namespace XCG.Generators.Cpp
{
    internal enum EType
    {
        None,
        Void,
        Auto,
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
        internal static string GetCppType(this EType type, CppOptions cppOptions)
        {
            return type switch
            {
                EType.None => String.Empty,
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
                EType.Token => String.Concat(cppOptions.TypePrefix, cppOptions.TokenName),
                _ => throw new NotImplementedException(),
            };
        }
    }
}
