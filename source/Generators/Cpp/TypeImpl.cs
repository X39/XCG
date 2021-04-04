namespace XCG.Generators.Cpp
{
    internal struct TypeImpl
    {
        public EType Type { get; init; }
        public int ReferenceCount { get; init; }
        public int PointerCount { get; init; }
        public string Name { get; init; }

        public override string ToString()
        {
            return $"{this.Type.GetCppType()}{new string('*', this.PointerCount)}{new string('&', this.ReferenceCount)} {this.Name}";
        }
    }
}
