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
            if (!usage.HasFlag(EUsage.Header)) return;
            writer.Write(whitespace);
            writer.WriteLine("{");
            var subWhitespace = string.Concat("    ", whitespace);
            foreach (var part in Parts)
            {
                part.WriteHeader(options, writer, subWhitespace);
            }

            writer.Write(whitespace);
            writer.WriteLine("}");
        }

        public override void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace)
        {
            if (!usage.HasFlag(EUsage.Implementation)) return;
            writer.Write(whitespace);
            writer.WriteLine("{");
            var subWhitespace = string.Concat("    ", whitespace);
            foreach (var part in Parts)
            {
                part.WriteImplementation(options, writer, subWhitespace);
            }

            writer.Write(whitespace);
            writer.WriteLine("}");
        }
    }
}