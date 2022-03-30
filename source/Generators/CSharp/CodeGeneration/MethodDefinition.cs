using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;

namespace XCG.Generators.CSharp.CodeGeneration;

internal class MethodDefinition : ICSharpContainerBase, IHasName
{
    private EType ReturnType { get; }

    /// <summary>
    /// The exact type returned.
    /// If provided, <see cref="ReturnType"/> is ignored.
    /// </summary>
    public string? ReturnTypeString { get; }

    public string Name { get; }
    public string FullName => BaseName is null ? Name : string.Concat(BaseName, ".", Name);
    public IEnumerable<ArgImpl> Arguments { get; }
    public string? AfterMethodImpl { get; init; }
    public bool IsVirtual { get; internal set; }

    public MethodDefinition(EType returnType, string name, string? afterMethodImpl, IEnumerable<ArgImpl> arguments)
    {
        ReturnType = returnType;
        AfterMethodImpl = afterMethodImpl;
        Name = name;
        Arguments = new ReadOnlyCollection<ArgImpl>(arguments.ToList());
    }

    public MethodDefinition(EType returnType, string name, IEnumerable<ArgImpl> arguments) : this(returnType, name,
        null, arguments)
    {
    }

    public MethodDefinition(EType returnType, string name) : this(returnType, name, null,
        Array.Empty<ArgImpl>() as IEnumerable<ArgImpl>)
    {
    }

    public MethodDefinition(EType returnType, string name, string afterMethodImpl) : this(returnType, name,
        afterMethodImpl, Array.Empty<ArgImpl>() as IEnumerable<ArgImpl>)
    {
    }

    public MethodDefinition(EType returnType, string name, params ArgImpl[] arguments) : this(returnType, name,
        null, arguments as IEnumerable<ArgImpl>)
    {
    }

    public MethodDefinition(EType returnType, string name, string afterMethodImpl, params ArgImpl[] arguments) :
        this(returnType, name, afterMethodImpl, arguments as IEnumerable<ArgImpl>)
    {
    }

    public MethodDefinition(string returnType, string name, string? afterMethodImpl, IEnumerable<ArgImpl> arguments)
    {
        ReturnTypeString = returnType;
        AfterMethodImpl = afterMethodImpl;
        Name = name;
        Arguments = new ReadOnlyCollection<ArgImpl>(arguments.ToList());
    }

    public MethodDefinition(string returnType, string name, IEnumerable<ArgImpl> arguments) : this(returnType, name,
        null, arguments)
    {
    }

    public MethodDefinition(string returnType, string name) : this(returnType, name, null,
        Array.Empty<ArgImpl>() as IEnumerable<ArgImpl>)
    {
    }

    public MethodDefinition(string returnType, string name, string afterMethodImpl) : this(returnType, name,
        afterMethodImpl, Array.Empty<ArgImpl>() as IEnumerable<ArgImpl>)
    {
    }

    public MethodDefinition(string returnType, string name, params ArgImpl[] arguments) : this(returnType, name,
        null, arguments as IEnumerable<ArgImpl>)
    {
    }

    public MethodDefinition(string returnType, string name, string afterMethodImpl, params ArgImpl[] arguments) :
        this(returnType, name, afterMethodImpl, arguments as IEnumerable<ArgImpl>)
    {
    }

    public override void WriteImplementation(CSharpOptions options, StreamWriter writer, string whitespace)
    {
        WriteImplementationActual(options, writer, whitespace);
    }

    private void WriteImplementationActual(CSharpOptions cSharpOptions, StreamWriter writer, string whitespace)
    {
        writer.Write(whitespace);
        if (ReturnTypeString is null)
        {
            writer.Write(ReturnType.ToCppString(cSharpOptions));
            writer.Write(" ");
        }
        else if (!string.IsNullOrWhiteSpace(ReturnTypeString))
        {
            writer.Write(ReturnTypeString);
            writer.Write(" ");
        }

        writer.Write(FullName);
        writer.Write("(");
        writer.Write(string.Join(", ", Arguments.Select((q) => q.ToString(cSharpOptions))));
        writer.Write(")");
        writer.WriteLine(AfterMethodImpl ?? string.Empty);

        writer.Write(whitespace);
        writer.WriteLine("{");

        var subWhitespace = string.Concat(whitespace, "    ");
        foreach (var generatorPart in Parts)
        {
            generatorPart.WriteImplementation(cSharpOptions, writer, subWhitespace);
        }

        writer.Write(whitespace);
        writer.WriteLine("}");
    }
}