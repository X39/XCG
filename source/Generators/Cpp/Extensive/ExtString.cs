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
                case "auto":
                case "bool":
                case "case":
                case "char":
                case "class":
                case "const":
                case "default":
                case "do":
                case "double":
                case "else":
                case "export":
                case "false":
                case "float":
                case "for":
                case "if":
                case "import ":
                case "inline":
                case "int":
                case "long":
                case "module":
                case "mutable":
                case "namespace":
                case "operator":
                case "private":
                case "protected":
                case "public":
                case "register":
                case "return":
                case "short":
                case "std":
                case "static":
                case "struct":
                case "sizeof":
                case "switch":
                case "template":
                case "this":
                case "true":
                case "typeof":
                case "typename":
                case "using":
                case "virtual":
                case "while":
                    return String.Concat(name, '_');
            }
        }
    }
}
