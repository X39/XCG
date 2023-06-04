using X39.Systems.XCG.Generators.Base;

namespace X39.Systems.XCG.Generators.CSharp;

public class CSharpOptions
{
    [GeneratorOption("namespace")]
    public string Namespace { get; init; } = "XCG.Parser";
}