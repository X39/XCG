namespace XCG.Parsing
{
    public interface IMatchPart : IPart
    {
        bool IsOptional { get; set; }
        bool IsCaptured { get; set; }
        bool IsAlias { get; set; }
        string? CaptureName { get; set; }
    }
}