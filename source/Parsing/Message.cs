namespace XCG.Parsing
{
    public class Message
    {
        public string Identifier { get; set; }
        public string Text { get; internal set; }
        public ESeverity Severity { get; internal set; }
        public Diagnostic Diagnostics { get; internal set; }
    }
}