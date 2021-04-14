using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;

namespace XCG.Generators.Cpp
{
    internal class MethodDefinition : CppContainerBase
    {
        public EType ReturnType { get; }

        /// <summary>
        /// The exact type returned.
        /// If provided, <see cref="ReturnType"/> is ignored.
        /// </summary>
        public string? ReturnTypeString { get; }
        public string Name { get; }
        public string FullName => this.BaseName is null ? this.Name : String.Concat(this.BaseName, "::", this.Name);
        public IEnumerable<ArgImpl> Arguments { get; }
        public string? AfterMethodImpl { get; init; }
        public bool HeaderOnly { get; init; }
        public bool IsVirtual { get; internal set; }

        public MethodDefinition(EType returnType, string name, string? afterMethodImpl, IEnumerable<ArgImpl> arguments)
        {
            this.ReturnType = returnType;
            this.AfterMethodImpl = afterMethodImpl;
            this.Name = name;
            this.Arguments = new ReadOnlyCollection<ArgImpl>(arguments.ToList());
        }
        public MethodDefinition(EType returnType, string name, IEnumerable<ArgImpl> arguments) : this(returnType, name, null, arguments) { }
        public MethodDefinition(EType returnType, string name) : this(returnType, name, null, Array.Empty<ArgImpl>() as IEnumerable<ArgImpl>) { }
        public MethodDefinition(EType returnType, string name, string afterMethodImpl) : this(returnType, name, afterMethodImpl, Array.Empty<ArgImpl>() as IEnumerable<ArgImpl>) { }
        public MethodDefinition(EType returnType, string name, params ArgImpl[] arguments) : this(returnType, name, null, arguments as IEnumerable<ArgImpl>) { }
        public MethodDefinition(EType returnType, string name, string afterMethodImpl, params ArgImpl[] arguments) : this(returnType, name, afterMethodImpl, arguments as IEnumerable<ArgImpl>) { }

        public MethodDefinition(string returnType, string name, string? afterMethodImpl, IEnumerable<ArgImpl> arguments)
        {
            this.ReturnTypeString = returnType;
            this.AfterMethodImpl = afterMethodImpl;
            this.Name = name;
            this.Arguments = new ReadOnlyCollection<ArgImpl>(arguments.ToList());
        }
        public MethodDefinition(string returnType, string name, IEnumerable<ArgImpl> arguments) : this(returnType, name, null, arguments) { }
        public MethodDefinition(string returnType, string name) : this(returnType, name, null, Array.Empty<ArgImpl>() as IEnumerable<ArgImpl>) { }
        public MethodDefinition(string returnType, string name, string afterMethodImpl) : this(returnType, name, afterMethodImpl, Array.Empty<ArgImpl>() as IEnumerable<ArgImpl>) { }
        public MethodDefinition(string returnType, string name, params ArgImpl[] arguments) : this(returnType, name, null, arguments as IEnumerable<ArgImpl>) { }
        public MethodDefinition(string returnType, string name, string afterMethodImpl, params ArgImpl[] arguments) : this(returnType, name, afterMethodImpl, arguments as IEnumerable<ArgImpl>) { }

        public override void WriteHeader(CppOptions cppOptions, StreamWriter writer, string whitespace)
        {
            if (this.HeaderOnly)
            {
                this.WriteImplementationActual(cppOptions, writer, whitespace);
                return;
            }
            writer.Write(whitespace);
            if (IsVirtual)
            {
                writer.Write("virtual ");
            }
            if (this.ReturnTypeString is null)
            {
                writer.Write(this.ReturnType.GetCppType(cppOptions));
                writer.Write(" ");
            }
            else if (!String.IsNullOrWhiteSpace(this.ReturnTypeString))
            {
                writer.Write(this.ReturnTypeString);
                writer.Write(" ");
            }
            writer.Write(this.FullName);
            writer.Write("(");
            writer.Write(String.Join(", ", this.Arguments.Select((q) => q.ToString(cppOptions))));
            writer.WriteLine(");");
        }

        public override void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace)
        {
            if (!this.HeaderOnly)
            {
                this.WriteImplementationActual(options, writer, whitespace);
            }
        }
        private void WriteImplementationActual(CppOptions cppOptions, StreamWriter writer, string whitespace)
        {
            writer.Write(whitespace);
            if (this.ReturnTypeString is null)
            {
                writer.Write(this.ReturnType.GetCppType(cppOptions));
                writer.Write(" ");
            }
            else if (!String.IsNullOrWhiteSpace(this.ReturnTypeString))
            {
                writer.Write(this.ReturnTypeString);
                writer.Write(" ");
            }
            writer.Write(this.FullName);
            writer.Write("(");
            writer.Write(String.Join(", ", this.Arguments.Select((q) => q.ToString(cppOptions))));
            writer.Write(")");
            writer.WriteLine(this.AfterMethodImpl ?? String.Empty);

            writer.Write(whitespace);
            writer.WriteLine("{");

            string? subWhitespace = String.Concat(whitespace, "    ");
            foreach (var generatorPart in this.Parts)
            {
                generatorPart.WriteImplementation(cppOptions, writer, subWhitespace);
            }

            writer.Write(whitespace);
            writer.WriteLine("}");
        }
    }
}
