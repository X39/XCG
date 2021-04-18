using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.IO;
using System.Linq;

namespace XCG.Generators.Cpp
{
    internal class CaptureDefinition : ICppPart
    {
        public string? BaseName { get; set; }
        public List<TypeImpl> Types { get; set; }
        public string Name { get; init; }

        public CaptureDefinition(string name, params TypeImpl[] typeImpls) : this(name, typeImpls as IEnumerable<TypeImpl>) {}
        public CaptureDefinition(string name, IEnumerable<TypeImpl> typeImpls)
        {
            Contract.Assert(!name.Contains('-'));
            Contract.Assert(!name.Contains('@'));
            this.Name = name;
            this.Types = typeImpls.ToList();
        }
        public void WriteHeader(CppOptions cppOptions, StreamWriter writer, string whitespace)
        {
            if (this.Types.Count == 0)
            {
                return;
            }
            else if (this.Types.Count == 1)
            {
                var typeImpl = this.Types.First();
                writer.Write(whitespace);
                writer.Write(typeImpl.ToString(cppOptions));
                writer.Write($" ");
                writer.Write(this.Name);
                writer.WriteLine(";");
            }
            else
            {
                writer.Write(whitespace);
                writer.Write($"std::variant<");
                bool isFirst = true;
                foreach (var typeImpl in this.Types)
                {
                    if (isFirst) { isFirst = false; } else { writer.Write(", "); }
                    writer.Write(typeImpl.ToString(cppOptions));
                }
                writer.Write($"> ");
                writer.Write(this.Name);
                writer.WriteLine(";");
            }
        }

        public void WriteImplementation(CppOptions cppOptions, StreamWriter writer, string whitespace)
        {
        }
    }
}
