using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Generators.Cpp
{
    public enum EValueConstant
    {
        None,
        EmptyClosure,
        True,
        False,
        NullChar,
    }
    internal static class EValueConstantExtensions
    {
        internal static string ToCppString(this EValueConstant type)
        {
            return type switch
            {
                EValueConstant.None => String.Empty,
                EValueConstant.EmptyClosure => "{}",
                EValueConstant.True => "true",
                EValueConstant.False => "false",
                EValueConstant.NullChar => "'\\0'",
                _ => throw new NotImplementedException(),
            };
        }
    }
}
