using System.Collections.Generic;
using System.Collections.Immutable;
using XCG.Generators.Base.Contracts;
using XCG.Generators.Base.Parts;

namespace XCG.Generators.Base.Expressions;

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