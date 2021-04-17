using System;

namespace XCG.Generators.Cpp
{
    internal struct TypeImpl : IEquatable<TypeImpl>
    {
        public EType Type { get; init; }

        /// <summary>
        /// If set, overrides <see cref="Type"/>.
        /// Will be used directly for output.
        /// </summary>
        public string? TypeString { get; init; }
        public int ReferenceCount { get; init; }
        public int PointerCount { get; init; }
        public bool IsConst { get; init; }

        public override bool Equals(object? obj)
        {
            return obj is TypeImpl impl && this.Equals(impl);
        }

        public bool Equals(TypeImpl other)
        {
            return this.Type == other.Type &&
                   this.TypeString == other.TypeString &&
                   this.ReferenceCount == other.ReferenceCount &&
                   this.PointerCount == other.PointerCount;
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(this.Type, this.TypeString, this.ReferenceCount, this.PointerCount);
        }

        public string ToString(CppOptions cppOptions)
        {
            return $"{(IsConst ? "const " : String.Empty)}{(TypeString ?? this.Type.GetCppType(cppOptions))}{new string('*', this.PointerCount)}{new string('&', this.ReferenceCount)}";
        }
    }
}
