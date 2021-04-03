namespace XCG.Parsing
{
    public struct CharacterRange : IPart
    {
        public char Start { get; set; }
        public char End { get; set; }
        public Diagnostic Diagnostics { get; set; }

        public CharacterRange(char start, char end, Diagnostic diagnostic)
        {
            this.Start = start;
            this.End = end;
            this.Diagnostics = diagnostic;
        }
        public override string ToString() => $@"range: `{this.Start}-{this.End}`";
    }
}