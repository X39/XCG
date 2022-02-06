using System;
using System.Collections.Generic;
using XCG.Generators.Cpp.CodeGeneration;

namespace XCG.Generators.Cpp;

public class CppOptions
{
    [CppOption("class", Nullable = false)] public string ClassName { get; set; } = "instance";

    [CppOption("token", Nullable = false)] public string TokenName { get; set; } = "token";

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

    [CppOption("create-string-tree")] public bool CreateStringTree { get; set; } = true;

    [CppOption("create-visitor")] public bool CreateVisitor { get; set; } = true;

    [CppOption("debug")] public bool Debug { get; set; } = false;

    internal Dictionary<object, CaptureDefinition> ClassCaptureDefinitionsMap { get; } =
        new();

    internal Dictionary<(string StateClassName, string Property), CaptureDefinition>
        StateCaptureDefinitionsMap { get; } =
        new();

    public string RootClassName => string.Concat(NamespaceName ?? string.Empty,
        NamespaceName is null ? string.Empty : "::", ClassName, "::");

    /// <summary>
    /// An internal counter, allowing to create variables
    /// collision-free.
    /// </summary>
    private int Counter { get; set; }

    internal string ToUnique(string value)
    {
        return string.Concat(value, ++Counter);
    }

    private Dictionary<object, MethodDefinition> MethodCache { get; } = new();

    internal MethodDefinition FromCache<T>(T target)
    {
        if (target is null)
        {
            throw new ArgumentNullException(nameof(target));
        }

        return MethodCache[target];
    }

    internal MethodDefinition FromCacheOrCreate<T>(T target, Func<T, MethodDefinition> action)
    {
        if (target is null)
        {
            throw new ArgumentNullException(nameof(target));
        }

        if (MethodCache.TryGetValue(target, out var cached)) return cached;
        cached = action(target);
        MethodCache[target] = cached;
        return cached;
    }
}