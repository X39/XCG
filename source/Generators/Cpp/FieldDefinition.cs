using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Generators.Cpp
{
    internal class FieldDefinition : ICppPart, IHasName
    {
        public string? BaseName { get; set; }
        public ArgImpl Type { get; set; }
        public string Name => this.Type.Name;

        public FieldDefinition(ArgImpl typeImpl)
        {
            this.Type = typeImpl;
        }
        public void WriteHeader(CppOptions cppOptions, StreamWriter writer, string whitespace)
        {
            writer.Write(whitespace);
            writer.Write(Type.ToString(cppOptions));
            writer.WriteLine(";");
        }

        public void WriteImplementation(CppOptions cppOptions, StreamWriter writer, string whitespace)
        {
        }
    }
}
