﻿using XCG.Generators.Base.Contracts;

namespace XCG.Generators.Base.Expressions;

public class EqualExpression : ICodeExpression
{
    public ICodeExpression Left { get; }
    public ICodeExpression Right { get; }

    public EqualExpression(ICodeExpression left, ICodeExpression right)
    {
        Left = left;
        Right = right;
    }
}