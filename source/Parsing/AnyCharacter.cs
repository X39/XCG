namespace XCG.Parsing
{
    public struct AnyCharacter : IPart
    {
        public Diagnostic Diagnostics { get; internal set; }

        public override string ToString() => "any";
    }
}