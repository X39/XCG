using X39.Systems.XCG.Generators.Cpp.CodeGeneration;

namespace X39.Systems.XCG.Generators.Cpp.CstParsing;

internal static class ExtString
{
    public static string ToCppSharedPtrType(this string str)
    {
        return string.Concat("std::shared_ptr<", str, ">");
    }
    public static ICppPart ToCppPart(this string str, EUsage usage = EUsage.Implementation)
    {
        return new FullBody(usage) { str };
    }
    public static string ToCppSharedPtrMake(this string str, params string[] args)
    {
        return string.Concat("std::make_shared<", str, ">(", string.Join(", ", args), ")");
    }
    public static string ToCppName(this string str)
    {
        var name = str.Replace('-', '_').Replace('@', '_').ToLower();
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
                return string.Concat(name, '_');
        }
    }
}