﻿using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace XCG.Generators.Cpp
{
    internal class CaptureDefinition : ICppPart
    {
        public string? BaseName { get; set; }
        public List<TypeImpl> Types { get; set; }
        public string Name { get; init; }

        public CaptureDefinition(string name, params TypeImpl[] typeImpls)
        {
            this.Name = name;
            this.Types = typeImpls.ToList();
        }
        public void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
        {
            if (this.Types.Count == 0)
            {
                return;
            }
            else if (this.Types.Count == 1)
            {
                var typeImpl = this.Types.First();
                writer.Write(whitespace);
                if (typeImpl.TypeString is null)
                {
                    writer.Write(typeImpl.ToString());
                }
                else
                {
                    writer.Write($"std::shared_ptr<");
                    writer.Write(typeImpl.ToString());
                    writer.Write($">");
                }
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
                    if (typeImpl.TypeString is null)
                    {
                        writer.Write(typeImpl.ToString());
                    }
                    else
                    {
                        writer.Write($"std::shared_ptr<");
                        writer.Write(typeImpl.ToString());
                        writer.Write($">");
                    }
                }
                writer.Write($"> ");
                writer.Write(this.Name);
                writer.WriteLine(";");
            }
        }

        public void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace)
        {
        }
    }
}