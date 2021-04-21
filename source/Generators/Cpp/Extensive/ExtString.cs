using System;

namespace XCG.Generators.Cpp.Extensive
{
    internal static class ExtString
    {
        public static string ToCppSharedPtrType(this string str)
        {
            return String.Concat("std::shared_ptr<", str, ">");
        }
        public static ICppPart ToCppPart(this string str, EUsage usage = EUsage.Implementation)
        {
            return new FullBody(usage) { str };
        }
        public static string ToCppSharedPtrMake(this string str, params string[] args)
        {
            return String.Concat("std::make_shared<", str, ">(", String.Join(", ", args), ")");
        }
        public static string ToCppName(this string str)
        {
            return String.Concat(str.Replace('-', '_').Replace('@', '_').ToLower());
        }
    }
}
