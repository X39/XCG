using System;
using System.Collections.Generic;

namespace XCG.Generators.CSharp.CstParsing;

internal static class ExtProduction
{
    public static string ToCppTypeName(this Parsing.Production production, CSharpOptions cSharpOptions, bool full)
    {
        return string.Concat(full ? cSharpOptions.RootClassName : string.Empty, cSharpOptions.TypePrefix,
            production.Identifier.ToCppName());
    }

    public static string ToCppStateTypeName(this Parsing.Production production, CSharpOptions cSharpOptions, bool full)
    {
        return string.Concat(production.ToCppTypeName(cSharpOptions, full), "_state");
    }

    public static string ToCppCanMatchMethodName(this Parsing.Production production, CSharpOptions cSharpOptions)
    {
        return string.Concat(cSharpOptions.MethodsPrefix, "p_can_", production.Identifier.ToCppName());
    }

    public static string ToCppMatchMethodName(this Parsing.Production production, CSharpOptions cSharpOptions)
    {
        return string.Concat(cSharpOptions.MethodsPrefix, "p_match_", production.Identifier.ToCppName());
    }

    public static IEnumerable<ICppPart> ToParts(this Parsing.Production production, CSharpOptions cSharpOptions)
    {
        var localsCount = 0;

        string ToUnique(string str) => string.Concat(str, (++localsCount).ToString());
        // Output matches
        foreach (var it in production.PrepareStatementMethods(production.ToCppTypeName(cSharpOptions, true),
                     production.ToCppStateTypeName(cSharpOptions, true), cSharpOptions))
        {
            yield return it;
        }

        // Generate can method
        var resettable = ToUnique("resettable");
        var canMatchMethodDefinition = new MethodDefinition(EType.Boolean,
            production.ToCppCanMatchMethodName(cSharpOptions),
            new ArgImpl {Name = Constants.DepthVariable, Type = EType.SizeT})
        {
            $@"resettable {resettable}(*this);",
            new VariableDefinition(
                new TypeImpl {TypeString = production.ToCppTypeName(cSharpOptions, true).ToCppSharedPtrType()},
                Constants.ClassInstanceFakeVariable),
            new VariableDefinition(new TypeImpl {TypeString = production.ToCppStateTypeName(cSharpOptions, false)},
                Constants.StateInstanceVariable),
        };
        var isFirst = true;
        foreach (var statement in production.Children)
        {
            switch (statement)
            {
                case Parsing.Statements.Match match:
                    canMatchMethodDefinition.Add(new IfPart(isIf: isFirst,
                        $@"!{cSharpOptions.FromCache(match).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
                    {
                        $@"{resettable}.reset();",
                        new DebugPart
                            {$@"trace(""Returning false on {production.Identifier}"", {Constants.DepthVariable});"},
                        new ReturnPart(EValueConstant.False),
                    });
                    break;
                case Parsing.Statements.Alternatives alternatives:
                    canMatchMethodDefinition.Add(new IfPart(isIf: isFirst,
                        $@"!{cSharpOptions.FromCache(alternatives).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
                    {
                        $@"{resettable}.reset();",
                        new DebugPart
                            {$@"trace(""Returning false on {production.Identifier}"", {Constants.DepthVariable});"},
                        new ReturnPart(EValueConstant.False),
                    });
                    break;
                case Parsing.Statements.If @if:
                    canMatchMethodDefinition.Add(new IfPart(isIf: isFirst,
                        $@"!{cSharpOptions.FromCache(@if).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
                    {
                        $@"{resettable}.reset();",
                        new DebugPart
                            {$@"trace(""Returning false on {production.Identifier}"", {Constants.DepthVariable});"},
                        new ReturnPart(EValueConstant.False),
                    });
                    break;
                case Parsing.Statements.While @while:
                    canMatchMethodDefinition.Add(new IfPart(isIf: isFirst,
                        $@"!{cSharpOptions.FromCache(@while).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
                    {
                        $@"{resettable}.reset();",
                        new DebugPart
                            {$@"trace(""Returning false on {production.Identifier}"", {Constants.DepthVariable});"},
                        new ReturnPart(EValueConstant.False),
                    });
                    break;
                case Parsing.Statements.Set:
                    continue;
                default:
                    throw new NotImplementedException();
            }

            isFirst = false;
        }

        canMatchMethodDefinition.Add(new DebugPart
            {$@"trace(""Returning true on {production.Identifier}"", {Constants.DepthVariable});"});
        canMatchMethodDefinition.Add(new ReturnPart(EValueConstant.True));
        yield return canMatchMethodDefinition;

        // Generate match method
        var matchMethodDefinition = new MethodDefinition(
            production.ToCppTypeName(cSharpOptions, true).ToCppSharedPtrType(),
            production.ToCppMatchMethodName(cSharpOptions),
            new ArgImpl {Name = Constants.DepthVariable, Type = EType.SizeT})
        {
            new VariableDefinition(EType.Auto, Constants.ClassInstanceVariable,
                production.ToCppTypeName(cSharpOptions, true).ToCppSharedPtrMake()),
            new VariableDefinition(
                new TypeImpl {TypeString = production.ToCppTypeName(cSharpOptions, true).ToCppSharedPtrType()},
                Constants.ClassInstanceFakeVariable),
            new VariableDefinition(new TypeImpl {TypeString = production.ToCppStateTypeName(cSharpOptions, false)},
                Constants.StateInstanceVariable),
        };
        foreach (var statement in production.Children)
        {
            resettable = ToUnique("resettable");
            matchMethodDefinition.Add($@"resettable {resettable}(*this);");
            switch (statement)
            {
                case Parsing.Statements.Match match:
                    matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.If,
                        $@"{cSharpOptions.FromCache(match).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
                    {
                        $@"{resettable}.reset();",
                        $@"{cSharpOptions.FromCache(match).Name}(false, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1);",
                    });
                    matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.Else, null)
                    {
                        $@"report(""Something moved wrong (todo: improve error messages)"", {Constants.DepthVariable});",
                    });
                    break;
                case Parsing.Statements.While @while:
                    matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.If,
                        $@"{cSharpOptions.FromCache(@while).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
                    {
                        $@"{resettable}.reset();",
                        $@"{cSharpOptions.FromCache(@while).Name}(false, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1);",
                    });
                    matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.Else, null)
                    {
                        $@"report(""Something moved wrong (todo: improve error messages)"", {Constants.DepthVariable});",
                    });
                    break;
                case Parsing.Statements.If @if:
                    matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.If,
                        $@"{cSharpOptions.FromCache(@if).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
                    {
                        $@"{resettable}.reset();",
                        $@"{cSharpOptions.FromCache(@if).Name}(false, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1);",
                    });
                    matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.Else, null)
                    {
                        $@"report(""Something moved wrong (todo: improve error messages)"", {Constants.DepthVariable});",
                    });
                    break;
                case Parsing.Statements.Alternatives alternatives:
                    matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.If,
                        $@"{cSharpOptions.FromCache(alternatives).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
                    {
                        $@"{resettable}.reset();",
                        $@"{cSharpOptions.FromCache(alternatives).Name}(false, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1);",
                    });
                    matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.Else, null)
                    {
                        $@"report(""Something moved wrong (todo: improve error messages)"", {Constants.DepthVariable});",
                    });
                    break;
                case Parsing.Statements.Set:
                    continue;
                default:
                    throw new NotImplementedException();
            }
        }

        matchMethodDefinition.Add($@"return {Constants.ClassInstanceVariable};");
        yield return matchMethodDefinition;
    }
}