using System.Collections;
using System.Collections.Generic;
using System.IO;

namespace XCG.Generators.Cpp
{
    internal class DebugPart : CppContainerBase
    {
        private readonly EUsage usage;
        public DebugPart(EUsage usage = EUsage.All)
        {
            this.usage = usage;
        }
        public override void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
        {
            if (options.Debug && usage.HasFlag(EUsage.Header))
            {
                foreach (var part in this.Parts)
                {
                    part.BaseName = this.BaseName;
                    part.WriteHeader(options, writer, whitespace);
                }
            }
        }
        public override void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace)
        {
            if (options.Debug && usage.HasFlag(EUsage.Implementation))
            {
                foreach (var part in this.Parts)
                {
                    part.BaseName = this.BaseName;
                    part.WriteImplementation(options, writer, whitespace);
                }
            }
        }
    }
}