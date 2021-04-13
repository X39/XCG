using System.Collections;
using System.Collections.Generic;
using System.IO;

namespace XCG.Generators.Cpp
{
    internal class WhileLoopPart : CppContainerBase
    {
        private readonly EUsage usage;
        private readonly string condition;
        #region ICppPart
        public WhileLoopPart(string condition, EUsage usage = EUsage.Implementation)
        {
            this.condition = condition;
            this.usage = usage;
        }
        public override void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
        {
            if (this.usage.HasFlag(EUsage.Header))
            {
                writer.Write(whitespace);
                writer.Write("while (");
                writer.Write(this.condition);
                writer.WriteLine(")");
                writer.Write(whitespace);
                writer.WriteLine("{");
                string? subWhitespace = System.String.Concat("    ", whitespace);
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
            if (this.usage.HasFlag(EUsage.Implementation))
            {
                writer.Write(whitespace);
                writer.Write("while (");
                writer.Write(this.condition);
                writer.WriteLine(")");
                writer.Write(whitespace);
                writer.WriteLine("{");
                string? subWhitespace = System.String.Concat("    ", whitespace);
                foreach (var part in this.Parts)
                {
                    part.WriteImplementation(options, writer, subWhitespace);
                }
                writer.Write(whitespace);
                writer.WriteLine("}");
            }
        }
        #endregion
    }
}