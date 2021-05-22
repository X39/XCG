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
            var name = String.Concat(str.Replace('-', '_').Replace('@', '_').ToLower());
            switch (name)
            {
                default: return name;
                case "class":
                case "namespace":
                case "switch":
                case "if":
                case "for":
                case "else":
                case "typename":
                case "template":
                case "return":
                case "while":
                case "do":
                case "public":
                case "static":
                case "private":
                case "protected":
                case "struct":
                case "virtual":
                case "operator":
                case "case":
                case "default":
                case "true":
                case "false":
                case "auto":
                case "int":
                case "bool":
                case "float":
                case "double":
                case "char":
                case "short":
                case "long":
                case "this":
                    return String.Concat(name, '_');
            }
        }
    }
}
