using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Generators.Cpp
{
    public class TokenRangeImpl : ICppPart
    {
        public string? BaseName { get; set; }
        public Parsing.CharacterRange CharacterRange { get; private set; }

        public TokenRangeImpl(Parsing.CharacterRange characterRange)
        {
            this.CharacterRange = characterRange;
        }
        public void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
        {
            // ToDo: Take into account full require here somehow
            writer.Write(whitespace);
            writer.WriteLine($"for (; current() >= '{CharacterRange.Start}' && current() <= '{CharacterRange.Start}' && next(););");
        }

        public void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace)
        {
            throw new NotImplementedException();
        }
    }
}
