using System.Collections;
using System.Collections.Generic;
using System.IO;

namespace XCG.Generators.Cpp
{
    internal class IfPart : CppContainerBase
    {
        public enum EIfScope
        {
            If,
            Else
        }
        private readonly EUsage usage;
        private readonly EIfScope ifScope;
        private readonly string? condition;
        public IfPart(EIfScope ifScope, string? condition, EUsage usage = EUsage.Implementation)
        {
            this.condition = condition;
            this.ifScope = ifScope;
            this.usage = usage;
        }
        public IfPart(bool isIf, string? condition, EUsage usage = EUsage.Implementation)
        {
            this.condition = condition;
            this.ifScope = isIf ? EIfScope.If : EIfScope.Else;
            this.usage = usage;
        }
        public override void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
        {
            if (usage.HasFlag(EUsage.Header))
            {
                writer.Write(whitespace);
                switch (this.ifScope)
                {
                    case EIfScope.If:
                        writer.WriteLine($@"if ({this.condition})");
                        break;
                    case EIfScope.Else:
                        if (this.condition is null)
                        {
                            writer.WriteLine($@"else");
                        }
                        else
                        {
                            writer.WriteLine($@"else if ({this.condition})");
                        }
                        break;
                }
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
                switch (this.ifScope)
                {
                    case EIfScope.If:
                        writer.WriteLine($@"if ({this.condition})");
                        break;
                    case EIfScope.Else:
                        if (this.condition is null)
                        {
                            writer.WriteLine($@"else");
                        }
                        else
                        {
                            writer.WriteLine($@"else if ({this.condition})");
                        }
                        break;
                }
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