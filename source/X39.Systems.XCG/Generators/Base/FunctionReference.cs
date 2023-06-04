using System.Collections.Generic;
using System.Collections.Immutable;
using X39.Systems.XCG.Generators.Base.Contracts;
using X39.Systems.XCG.Generators.Base.Expressions;
using X39.Systems.XCG.Generators.Base.Parts;

namespace X39.Systems.XCG.Generators.Base;

public class FunctionReference
{
    public Function Function { get; protected set; }

    public FunctionReference(Function function)
    {
        Function = function;
    }
    
    public FunctionCallExpression Call(params ICodeExpression[] expressions)
    {
        return new FunctionCallExpression(this, expressions);
    }
}