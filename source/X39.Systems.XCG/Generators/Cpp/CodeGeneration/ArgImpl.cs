namespace X39.Systems.XCG.Generators.Cpp.CodeGeneration;

internal readonly struct ArgImpl : IHasName
{
    public EType Type { get; init; }

    /// <summary>
    /// If set, overrides <see cref="Type"/>.
    /// Will be used directly for output.
    /// </summary>
    public string? TypeString { get; init; }
    public int ReferenceCount { get; init; }
    public string Name { get; init; }

    public string ToString(CppOptions cppOptions)
    {
        return $"{(TypeString ?? Type.ToCppString(cppOptions))}{new string('&', ReferenceCount)} {Name}";
    }
}