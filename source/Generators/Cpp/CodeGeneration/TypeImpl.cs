using System;

namespace XCG.Generators.Cpp.CodeGeneration;

internal readonly struct TypeImpl : IEquatable<TypeImpl>
{
    public EType Type { get; init; }

    /// <summary>
    /// If set, overrides <see cref="Type"/>.
    /// Will be used directly for output.
    /// </summary>
    public string? TypeString { get; init; }

    public int ReferenceCount { get; init; }
    public int PointerCount { get; init; }
    public bool IsConst { get; init; }

    public override bool Equals(object? obj)
    {
        return obj is TypeImpl impl && Equals(impl);
    }

    public bool Equals(TypeImpl other)
    {
        return Type == other.Type &&
               TypeString == other.TypeString &&
               ReferenceCount == other.ReferenceCount &&
               PointerCount == other.PointerCount;
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(Type, TypeString, ReferenceCount, PointerCount);
    }

    public string ToString(CppOptions cppOptions)
    {
        return
            $"{(IsConst ? "const " : string.Empty)}{(TypeString ?? Type.ToCppString(cppOptions))}{new string('*', PointerCount)}{new string('&', ReferenceCount)}";
    }
}