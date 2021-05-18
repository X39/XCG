namespace XCG.Generators.Cpp
{
    internal struct ArgImpl : IHasName
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

        public string ToString(CppOptions cppOptions)
        {
            return $"{(TypeString ?? this.Type.ToCppString(cppOptions))}{new string('*', this.PointerCount)}{new string('&', this.ReferenceCount)} {this.Name}";
        }
    }
}
