using XCG.Generators.Base;

namespace XCG.Generators.CSharp;

public class CSharpOptions
{
    [GeneratorOption("namespace")]
    public string Namespace { get; init; } = "XCG.Parser";
}