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

        [CppOption("create-string-tree-spaces")]
        public int CreateStringTreeSpaces { get; set; } = 2;

        [CppOption("console-color-capture-name")]
        public bool ConsoleColorCaptureName { get; set; } = true;

        [CppOption("create-string-tree")]
        public bool CreateStringTree { get; set; } = true;

        [CppOption("create-visitor")]
        public bool CreateVisitor { get; set; } = true;

        [CppOption("debug")]
        public bool Debug { get; set; } = false;

        internal Dictionary<object, CaptureDefinition> ClassCaptureDefinitionsMap { get; } = new Dictionary<object, CaptureDefinition>();
        internal Dictionary<(string StateClassName, string Property), CaptureDefinition> StateCaptureDefinitionsMap { get; } = new Dictionary<(string StateClassName, string Property), CaptureDefinition>();
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