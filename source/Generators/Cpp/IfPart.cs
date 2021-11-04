using System;
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

        private readonly EUsage _usage;
        private readonly EIfScope _ifScope;
        private readonly string? _condition;

        public IfPart(EIfScope ifScope, string? condition, EUsage usage = EUsage.Implementation)
        {
            this._condition = condition;
            this._ifScope = ifScope;
            this._usage = usage;
        }

        public IfPart(bool isIf, string? condition, EUsage usage = EUsage.Implementation)
        {
            this._condition = condition;
            _ifScope = isIf ? EIfScope.If : EIfScope.Else;
            this._usage = usage;
        }

        public override void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
        {
            if (!_usage.HasFlag(EUsage.Header)) return;
            writer.Write(whitespace);
            switch (_ifScope)
            {
                case EIfScope.If:
                    writer.WriteLine($@"if ({_condition})");
                    break;
                case EIfScope.Else:
                    writer.WriteLine(_condition is null ? $@"else" : $@"else if ({_condition})");

                    break;
                default:
                    throw new ArgumentOutOfRangeException();
            }

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
            if (!_usage.HasFlag(EUsage.Implementation)) return;
            writer.Write(whitespace);
            switch (_ifScope)
            {
                case EIfScope.If:
                    writer.WriteLine($@"if ({_condition})");
                    break;
                case EIfScope.Else:
                    writer.WriteLine(_condition is null ? $@"else" : $@"else if ({_condition})");

                    break;
                default:
                    throw new ArgumentOutOfRangeException();
            }

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