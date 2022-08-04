using System;

namespace XCG.Generators.Base;

[AttributeUsage(AttributeTargets.Property)]
internal class OptionAttribute : Attribute
{
    public OptionAttribute(string v)
    {
        Name = v;
    }

    public string Name { get; }
    public bool Nullable { get; set; }
}