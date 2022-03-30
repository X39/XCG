namespace XCG.Generators.CSharp.CodeGeneration;

internal readonly struct ArgImpl : IHasName
{
    public EType Type { get; init; }

    /// <summary>
    /// If set, overrides <see cref="Type"/>.
    /// Will be used directly for output.
    /// </summary>
    public string? TypeString { get; init; }
    public string Name { get; init; }

    public string ToString(CSharpOptions cSharpOptions)
    {
        return $"public {(TypeString ?? Type.ToCppString(cSharpOptions))} {Name}";
    }
}