using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Generators.Cpp
{
    internal class FieldDefinition : ICppPart
    {
        public string? BaseName { get; set; }
        public TypeImpl Type { get; set; }

        public FieldDefinition(TypeImpl typeImpl)
        {
            this.Type = typeImpl;
        }
        public void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
        {
            writer.Write(whitespace);
            writer.Write(Type.ToString());
            writer.WriteLine(";");
        }

        public void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace)
        {
        }
    }
}
