namespace XCG.Generators.Base;

public static class Constants
{
    public static class Groups
    {
        public const string Tokenizer = "Tokenzier";
    }

    public static class Functions
    {
        public const string Skip = "Skip";
        public const string StoreState = "StoreState";
    }

    public static class States
    {
        public const string ParsingOffset = "ParsingOffset";
        public const string ParsingLine = "ParsingLine";
        public const string ParsingColumn = "ParsingColumn";
        public const string ParsingContents = "ParsingContents";
        public const string ParsingContentsLength = "ParsingContentsLength";
    }

    public static class Parameters
    {
    }

    public static class VariablePrefixes
    {
        public const string ResetHolder = "ResetHolder";
        public const string Temporary = "Temporary";
    }

    public static class Variables
    {
        public const string Count = "count";
    }
}