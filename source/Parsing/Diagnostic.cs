namespace XCG.Parsing
{
    public struct Diagnostic
    {
        public int Line { get; set; }
        public int Column { get; set; }
        public int Offset { get; set; }
        public string File { get; set; }
    }
}