using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;

namespace XCG.Generators.Cpp
{
    internal class EnumDefinition : ICppPart
    {
        public string Name { get; }
        public string? BaseName { get; set; }
        public string FullName => this.BaseName is null ? this.Name : String.Concat(this.BaseName, "::", this.Name);

        public List<string> Entries { get; init; }
        public EnumDefinition(string name)
        {
            Entries = new List<string>();
            this.Name = name;
        }
        public void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
        {
            writer.Write(whitespace);
            writer.Write("enum class ");
            writer.WriteLine(this.FullName);

            writer.Write(whitespace);
            writer.WriteLine("{");

            var subWhitespace = whitespace + "    ";
            foreach(var entry in this.Entries)
            {
                writer.Write(subWhitespace);
                writer.Write(entry);
                writer.WriteLine(",");
            }
            writer.Write(subWhitespace);
            writer.WriteLine("__MAX__");

            writer.Write(whitespace);
            writer.WriteLine("};");
        }

        public void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace)
        {
        }
    }
}
