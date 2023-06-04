using System.Collections.Generic;
using System.Collections.Immutable;
using X39.Systems.XCG.Generators.Base.Contracts;
using X39.Systems.XCG.Generators.Base.Parts;

namespace X39.Systems.XCG.Generators.Base.Expressions;

public class FunctionCallExpression : ICodeExpression
{
    public FunctionReference FunctionReference { get; }
    public IReadOnlyCollection<ICodeExpression> Arguments { get; }

    public FunctionCallExpression(FunctionReference functionReference, IEnumerable<ICodeExpression> expressions)
    {
        FunctionReference = functionReference;
        Arguments = expressions.ToImmutableArray();
    }
}