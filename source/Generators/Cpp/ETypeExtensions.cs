using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Generators.Cpp
{
    internal static class ETypeExtensions
    {
        internal static string GetCppType(this EType type)
        {
            return type switch
            {
                EType.Void => "void",
                EType.Boolean => "bool",
                EType.Float => "float",
                EType.Double => "double",
                EType.Int32 => "int",
                EType.Int64 => "long",
                EType.String => "std::string",
                EType.StringView => "std::string_view",
                EType.SizeT => "size_t",
                _ => throw new NotImplementedException(),
            };
        }
    }
}
