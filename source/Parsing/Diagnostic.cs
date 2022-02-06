namespace XCG.Parsing
{
    public struct Diagnostic
    {
        public int Line { get; init; }
        public int Column { get; set; }
        public int Offset { get; set; }
        public string File { get; init; }
    }
}