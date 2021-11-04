using System.IO;

namespace XCG.Generators.Cpp
{
    internal class DebugPart : CppContainerBase
    {
        private readonly EUsage _usage;

        public DebugPart(EUsage usage = EUsage.All)
        {
            this._usage = usage;
        }

        public override void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
        {
            if (!options.Debug || !_usage.HasFlag(EUsage.Header)) return;
            foreach (var part in Parts)
            {
                part.BaseName = BaseName;
                part.WriteHeader(options, writer, whitespace);
            }
        }

        public override void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace)
        {
            if (!options.Debug || !_usage.HasFlag(EUsage.Implementation)) return;
            foreach (var part in Parts)
            {
                part.BaseName = BaseName;
                part.WriteImplementation(options, writer, whitespace);
            }
        }
    }
}