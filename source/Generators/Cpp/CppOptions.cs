using System;
using System.Collections.Generic;

namespace XCG.Generators.Cpp
{
    public class CppOptions
    {
        [CppOption("class", Nullable = false)]
        public string ClassName { get; set; } = "instance";

        [CppOption("token", Nullable = false)]
        public string TokenName { get; set; } = "token";

        [CppOption("token-enum", Nullable = false)]
        public string TokenEnumName { get; set; } = "tok";

        [CppOption("file-header", Nullable = false)]
        public string HeaderFileName { get; set; } = "parser.hpp";

        [CppOption("file-impl", Nullable = false)]
        public string ImplementationFileName { get; set; } = "parser.cpp";

        [CppOption("namespace", Nullable = true)]
        public string? NamespaceName { get; set; } = null;

        [CppOption("prefix-method", Nullable = true)]
        public string? MethodsPrefix { get; set; } = null;

        [CppOption("prefix-type", Nullable = true)]
        public string? TypePrefix { get; set; } = null;


        public string RootClassName => String.Concat(this.NamespaceName ?? String.Empty, this.NamespaceName is null ? String.Empty : "::", this.ClassName, "::");
        /// <summary>
        /// An internal counter, allowing to create variables
        /// collission-free.
        /// </summary>
        internal int Counter { get; set; } = 0;

        internal string ToUnique(string value)
        {
            return String.Concat(value, ++this.Counter);
        }

        private Dictionary<object, MethodDefinition> MethodCache { get; } = new Dictionary<object, MethodDefinition>();

        internal MethodDefinition FromCache<T>(T target)
        {
            if (target is null) { throw new ArgumentNullException(nameof(target)); }
            return this.MethodCache[target];
        }
        internal MethodDefinition FromCacheOrCreate<T>(T target, Func<T, MethodDefinition> action)
        {
            if (target is null) { throw new ArgumentNullException(nameof(target)); }
            if (!this.MethodCache.TryGetValue(target, out var cached))
            {
                cached = action(target);
                this.MethodCache[target] = cached;
            }
            return cached;
        }
    }
}