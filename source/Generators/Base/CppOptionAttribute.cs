using System;

namespace XCG.Generators.Base;

[AttributeUsage(AttributeTargets.Property)]
internal class GeneratorOptionAttribute : Attribute
{
    public GeneratorOptionAttribute(string v)
    {
        Name = v;
    }

    public string Name { get; }
    public string Description { get; set; }
}