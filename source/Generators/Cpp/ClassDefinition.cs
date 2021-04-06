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
        public List<ICppPart> PrivateParts { get; init; }
        public List<ICppPart> ProtectedParts { get; init; }
        public List<ICppPart> PublicParts { get; init; }
        public ClassDefinition(string name)
        {
            this.Name = name;
            this.PrivateParts = new();
            this.ProtectedParts = new();
            this.PublicParts = new();
        }
        public void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
        {
            writer.Write(whitespace);
            writer.Write(!this.PrivateParts.Any() ? "struct " : "class ");
            writer.WriteLine(this.FullName);

            writer.Write(whitespace);
            writer.WriteLine("{");

            string? subWhitespace = String.Concat(whitespace, "    ");
            if (this.PrivateParts.Any())
            {
                writer.Write(whitespace);
                writer.WriteLine("private:");
                foreach (var generatorPart in this.PrivateParts)
                {
                    generatorPart.BaseName = null;
                    generatorPart.WriteHeader(options, writer, subWhitespace);
                }
            }

            if (this.ProtectedParts.Any())
            {
                writer.Write(whitespace);
                writer.WriteLine("protected:");
                foreach (var generatorPart in this.PublicParts)
                {
                    generatorPart.BaseName = null;
                    generatorPart.WriteHeader(options, writer, subWhitespace);
                }
            }

            if (this.PublicParts.Any())
            {
                if (this.PrivateParts.Any())
                {
                    writer.Write(whitespace);
                    writer.WriteLine("public:");
                }
                foreach (var generatorPart in this.PublicParts)
                {
                    generatorPart.BaseName = null;
                    generatorPart.WriteHeader(options, writer, subWhitespace);
                }
            }

            writer.Write(whitespace);
            writer.WriteLine("};");
        }

        public void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace)
        {
            foreach (var generatorPart in this.PrivateParts)
            {
                generatorPart.BaseName = this.FullName;
                generatorPart.WriteImplementation(options, writer, whitespace);
            }

            foreach (var generatorPart in this.ProtectedParts)
            {
                generatorPart.BaseName = this.FullName;
                generatorPart.WriteImplementation(options, writer, whitespace);
            }

            foreach (var generatorPart in this.PublicParts)
            {
                generatorPart.BaseName = this.FullName;
                generatorPart.WriteImplementation(options, writer, whitespace);
            }
        }
    }
}
