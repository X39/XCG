namespace XCG.Parsing
{
    public class Reference : IPart, IMatchPart
    {
        public object? Refered { get; set; }
        public string Text { get; set; }
        public bool IsOptional { get; set; }
        public bool IsCaptured { get; set; }
        public bool IsAlias { get; set; }
        public string? CaptureName { get; set; }

        public Reference(string text)
        {
            this.Refered = null;
            this.Text = text;
        }

        public override string ToString()
        {
            return $@"$ref: {this.Text} ({this.Refered ?? "NULL"})";
        }
    }
}
