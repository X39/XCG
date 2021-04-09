using System.Collections;
using System.Collections.Generic;
using System.IO;

namespace XCG.Generators.Cpp
{
    internal class ScopePart : CppContainerBase
    {
        private readonly EUsage usage;
        public ScopePart(EUsage usage = EUsage.Implementation)
        {
            this.usage = usage;
        }
        public override void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
        {
            if (usage.HasFlag(EUsage.Header))
            {
                writer.Write(whitespace);
                writer.WriteLine("{");
                var subWhitespace = string.Concat("    ", whitespace);
                foreach (var part in this.Parts)
                {
                    part.WriteHeader(options, writer, subWhitespace);
                }
                writer.Write(whitespace);
                writer.WriteLine("}");
            }
        }
        public override void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace)
        {
            if (usage.HasFlag(EUsage.Implementation))
            {
                writer.Write(whitespace);
                writer.WriteLine("{");
                var subWhitespace = string.Concat("    ", whitespace);
                foreach (var part in this.Parts)
                {
                    part.WriteImplementation(options, writer, subWhitespace);
                }
                writer.Write(whitespace);
                writer.WriteLine("}");
            }
        }
    }
}