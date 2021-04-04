using System;

namespace XCG.Generators.Cpp
{
    internal class CppOptionAttribute : Attribute
    {
        public CppOptionAttribute(string v)
        {
            this.Name = v;
        }

        public string Name { get; }
        public bool Nullable { get; set; }
    }
}