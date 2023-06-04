using System.Collections.Generic;

namespace X39.Systems.XCG.Parsing.TokenStatements;

public class Require : ITokenStatement, IHasDiagnostics
{
    public Multiplicity Range { get; set; }
    public List<IStatement> Parts { get; init; }
    public bool Negated { get; set; }
    public Diagnostic Diagnostics { get; internal init; }
    IEnumerable<IStatement> IStatement.Statements => Parts;

    public Require()
    {
        Parts = new List<IStatement>();
    }
}