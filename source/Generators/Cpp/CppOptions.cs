namespace XCG.Generators.Cpp
{
    public class CppOptions
    {
        [CppOption("file-header", Nullable = false)]
        public string HeaderFileName { get; set; } = "parser.hpp";

        [CppOption("file-impl", Nullable = false)]
        public string ImplementationFileName { get; set; } = "parser.cpp";

        [CppOption("namespace", Nullable = true)]
        public string? NamespaceName { get; set; } = null;
    }
}