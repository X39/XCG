namespace XCG.Parsing
{
    public struct CharacterRange : IPart
    {
        public char Start { get; set; }
        public char End { get; set; }

        public CharacterRange(char start, char end)
        {
            this.Start = start;
            this.End = end;
        }
        public override string ToString() => $@"range: `{this.Start}-{this.End}`";
    }
}