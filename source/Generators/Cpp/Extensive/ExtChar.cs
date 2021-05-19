using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Generators.Cpp.Extensive
{
    public static class ExtChar
    {
        public static string Escape(this char c)
        {
            switch(c)
            {
                default:
                    return c.ToString();
                case '\'':
                    return "\\'";
                case '\"':
                    return "\\\"";
                case '?':
                    return "\\?";
                case '\\':
                    return "\\\\";
                case '\a':
                    return "\\a";
                case '\b':
                    return "\\b";
                case '\f':
                    return "\\f";
                case '\n':
                    return "\\n";
                case '\r':
                    return "\\r";
                case '\t':
                    return "\\t";
                case '\v':
                    return "\\v";
                case '\0':
                    return "\\0";
            }
        }
    }
}
