namespace XCG.Generators.Cpp
{
    internal struct TypeImpl
    {
        public EType Type { get; init; }

        /// <summary>
        /// If set, overrides <see cref="Type"/>.
        /// Will be used directly for output.
        /// </summary>
        public string? TypeString { get; init; }
        public int ReferenceCount { get; init; }
        public int PointerCount { get; init; }
        public string Name { get; init; }

        public override string ToString()
        {
            return $"{(TypeString ?? this.Type.GetCppType())}{new string('*', this.PointerCount)}{new string('&', this.ReferenceCount)} {this.Name}";
        }
    }
}
