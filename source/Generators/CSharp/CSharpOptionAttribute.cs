using System;

namespace XCG.Generators.CSharp;

[AttributeUsage(AttributeTargets.Property)]
internal class CSharpOptionAttribute : Attribute
{
    public CSharpOptionAttribute(string v)
    {
        Name = v;
    }

    public string Name { get; }
    public bool Nullable { get; set; }
}