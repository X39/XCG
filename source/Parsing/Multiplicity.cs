namespace XCG.Parsing;

public struct Multiplicity : IHasDiagnostics
{
    /// <summary>
    /// The inclusive from value.
    /// A value of <see cref="int.MinValue"/> is considered to be negative infinity.
    /// </summary>
    public int From { get; set; }
    /// <summary>
    /// The inclusive to value.
    /// A value of <see cref="int.MaxValue"/> is considered to be positive infinity.
    /// </summary>
    public int To { get; set; }

    public bool IsOnce => To - From == 1;

    public Diagnostic Diagnostics { get; internal init; }

    public Multiplicity(int fromInclusive, int toExclusive, Diagnostic diagnostic)
    {
        From = fromInclusive;
        To = toExclusive;
        Diagnostics = diagnostic;
    }
    public Multiplicity(int exact, Diagnostic diagnostic)
    {
        From = exact;
        To = exact;
        Diagnostics = diagnostic;
    }
}