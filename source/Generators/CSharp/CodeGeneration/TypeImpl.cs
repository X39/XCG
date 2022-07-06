using System;

namespace XCG.Generators.CSharp.CodeGeneration;

internal readonly struct TypeImpl : IEquatable<TypeImpl>
{
    public EType Type { get; init; }

    /// <summary>
    /// If set, overrides <see cref="Type"/>.
    /// Will be used directly for output.
    /// </summary>
    public string? TypeString { get; init; }

    public override bool Equals(object? obj)
    {
        return obj is TypeImpl impl && Equals(impl);
    }

    public bool Equals(TypeImpl other)
    {
        return Type == other.Type &&
               TypeString == other.TypeString;
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(Type, TypeString);
    }

    public string ToString(CSharpOptions cSharpOptions)
    {
        return TypeString ?? Type.ToCSharpString(cSharpOptions);
    }
}