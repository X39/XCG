using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;
using XCG.Generators.Base.Parts;

namespace XCG.Generators.CSharp;

public class CSharpGenerator : Base.BaseGenerator<CSharpOptions>
{
    protected override async Task WriteFiles(
        IEnumerable<Group> functionGroups,
        string output,
        CancellationToken cancellationToken)
    {
        throw new NotImplementedException();
    }
}