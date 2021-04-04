using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace XCG.Generators.Cpp
{
    internal class ClassDefinition : ICppPart
    {
        public string? BaseName { get; set; }
        public string Name { get; }
        public string FullName => this.BaseName is null ? this.Name : String.Concat(this.BaseName, "::", this.Name);
        public List<TypeImpl> PrivateFields { get; init; }
        public List<TypeImpl> PublicFields { get; init; }
        public List<MethodDefinition> PrivateMethods { get; init; }
        public List<MethodDefinition> PublicMethods { get; init; }
        public ClassDefinition(string name)
        {
            this.Name = name;
            this.PrivateFields = new List<TypeImpl>();
            this.PublicFields = new List<TypeImpl>();
            this.PrivateMethods = new List<MethodDefinition>();
            this.PublicMethods = new List<MethodDefinition>();
        }
        public void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
        {
            writer.Write(whitespace);
            writer.Write("class ");
            writer.WriteLine(this.FullName);

            writer.Write(whitespace);
            writer.WriteLine("{");

            string? subWhitespace = String.Concat(whitespace, "    ");
            if (this.PrivateFields.Any() || this.PrivateMethods.Any())
            {
                writer.Write(whitespace);
                writer.WriteLine("private:");
            }
            foreach (var typeImpl in this.PrivateFields)
            {
                writer.Write(subWhitespace);
                writer.Write(typeImpl.ToString());
                writer.WriteLine(";");
            }
            foreach (var generatorPart in this.PrivateMethods)
            {
                generatorPart.BaseName = null;
                generatorPart.WriteHeader(options, writer, subWhitespace);
            }

            if (this.PublicFields.Any() || this.PublicMethods.Any())
            {
                writer.Write(whitespace);
                writer.WriteLine("public:");
            }
            foreach (var typeImpl in this.PublicFields)
            {
                writer.Write(subWhitespace);
                writer.Write(typeImpl.ToString());
                writer.WriteLine(";");
            }
            foreach (var generatorPart in this.PublicMethods)
            {
                generatorPart.BaseName = null;
                generatorPart.WriteHeader(options, writer, subWhitespace);
            }

            writer.Write(whitespace);
            writer.WriteLine("};");
        }

        public void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace)
        {
            foreach (var generatorPart in this.PrivateMethods)
            {
                generatorPart.BaseName = this.FullName;
                generatorPart.WriteImplementation(options, writer, whitespace);
            }

            foreach (var generatorPart in this.PublicMethods)
            {
                generatorPart.BaseName = this.FullName;
                generatorPart.WriteImplementation(options, writer, whitespace);
            }
        }
    }
}
