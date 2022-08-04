using System.Collections.Generic;
using System.Collections.Immutable;
using XCG.Generators.Base.Contracts;
using XCG.Generators.Base.Expressions;
using XCG.Generators.Base.Parts;

namespace XCG.Generators.Base;

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