using System;
using System.Collections.Generic;
using XCG.Generators.Cpp.CodeGeneration;

namespace XCG.Generators.Cpp.CstParsing;

internal static class ExtProduction
{
    public static string ToCppTypeName(this Parsing.Production production, CppOptions cppOptions, bool full)
    {
        return string.Concat(full ? cppOptions.RootClassName : string.Empty, cppOptions.TypePrefix,
            production.Identifier.ToCppName());
    }

    public static string ToCppStateTypeName(this Parsing.Production production, CppOptions cppOptions, bool full)
    {
        return string.Concat(production.ToCppTypeName(cppOptions, full), "_state");
    }

    public static string ToCppCanMatchMethodName(this Parsing.Production production, CppOptions cppOptions)
    {
        return string.Concat(cppOptions.MethodsPrefix, "p_can_", production.Identifier.ToCppName());
    }

    public static string ToCppMatchMethodName(this Parsing.Production production, CppOptions cppOptions)
    {
        return string.Concat(cppOptions.MethodsPrefix, "p_match_", production.Identifier.ToCppName());
    }

    public static IEnumerable<ICppPart> ToParts(this Parsing.Production production, CppOptions cppOptions)
    {
        var localsCount = 0;

        string ToUnique(string str) => string.Concat(str, (++localsCount).ToString());
        // Output matches
        foreach (var it in production.PrepareStatementMethods(production.ToCppTypeName(cppOptions, true),
                     production.ToCppStateTypeName(cppOptions, true), cppOptions))
        {
            yield return it;
        }

        // Generate can method
        var resettable = ToUnique("resettable");
        var canMatchMethodDefinition = new MethodDefinition(EType.Boolean,
            production.ToCppCanMatchMethodName(cppOptions),
            new ArgImpl {Name = Constants.DepthVariable, Type = EType.SizeT})
        {
            $@"resettable {resettable}(*this);",
            new VariableDefinition(
                new TypeImpl {TypeString = production.ToCppTypeName(cppOptions, true).ToCppSharedPtrType()},
                Constants.ClassInstanceFakeVariable),
            new VariableDefinition(new TypeImpl {TypeString = production.ToCppStateTypeName(cppOptions, false)},
                Constants.StateInstanceVariable),
        };
        var isFirst = true;
        foreach (var statement in production.Children)
        {
            switch (statement)
            {
                case Parsing.Statements.Match match:
                    canMatchMethodDefinition.Add(new IfPart(isIf: isFirst,
                        $@"!{cppOptions.FromCache(match).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
                    {
                        $@"{resettable}.reset();",
                        new DebugPart
                            {$@"trace(""Returning false on {production.Identifier}"", {Constants.DepthVariable});"},
                        new ReturnPart(EValueConstant.False),
                    });
                    break;
                case Parsing.Statements.Alternatives alternatives:
                    canMatchMethodDefinition.Add(new IfPart(isIf: isFirst,
                        $@"!{cppOptions.FromCache(alternatives).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
                    {
                        $@"{resettable}.reset();",
                        new DebugPart
                            {$@"trace(""Returning false on {production.Identifier}"", {Constants.DepthVariable});"},
                        new ReturnPart(EValueConstant.False),
                    });
                    break;
                case Parsing.Statements.If @if:
                    canMatchMethodDefinition.Add(new IfPart(isIf: isFirst,
                        $@"!{cppOptions.FromCache(@if).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
                    {
                        $@"{resettable}.reset();",
                        new DebugPart
                            {$@"trace(""Returning false on {production.Identifier}"", {Constants.DepthVariable});"},
                        new ReturnPart(EValueConstant.False),
                    });
                    break;
                case Parsing.Statements.While @while:
                    canMatchMethodDefinition.Add(new IfPart(isIf: isFirst,
                        $@"!{cppOptions.FromCache(@while).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
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
            production.ToCppTypeName(cppOptions, true).ToCppSharedPtrType(),
            production.ToCppMatchMethodName(cppOptions),
            new ArgImpl {Name = Constants.DepthVariable, Type = EType.SizeT})
        {
            new VariableDefinition(EType.Auto, Constants.ClassInstanceVariable,
                production.ToCppTypeName(cppOptions, true).ToCppSharedPtrMake()),
            new VariableDefinition(
                new TypeImpl {TypeString = production.ToCppTypeName(cppOptions, true).ToCppSharedPtrType()},
                Constants.ClassInstanceFakeVariable),
            new VariableDefinition(new TypeImpl {TypeString = production.ToCppStateTypeName(cppOptions, false)},
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
                        $@"{cppOptions.FromCache(match).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
                    {
                        $@"{resettable}.reset();",
                        $@"{cppOptions.FromCache(match).Name}(false, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1);",
                    });
                    matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.Else, null)
                    {
                        $@"report(""Something moved wrong (todo: improve error messages)"", {Constants.DepthVariable});",
                    });
                    break;
                case Parsing.Statements.While @while:
                    matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.If,
                        $@"{cppOptions.FromCache(@while).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
                    {
                        $@"{resettable}.reset();",
                        $@"{cppOptions.FromCache(@while).Name}(false, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1);",
                    });
                    matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.Else, null)
                    {
                        $@"report(""Something moved wrong (todo: improve error messages)"", {Constants.DepthVariable});",
                    });
                    break;
                case Parsing.Statements.If @if:
                    matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.If,
                        $@"{cppOptions.FromCache(@if).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
                    {
                        $@"{resettable}.reset();",
                        $@"{cppOptions.FromCache(@if).Name}(false, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1);",
                    });
                    matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.Else, null)
                    {
                        $@"report(""Something moved wrong (todo: improve error messages)"", {Constants.DepthVariable});",
                    });
                    break;
                case Parsing.Statements.Alternatives alternatives:
                    matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.If,
                        $@"{cppOptions.FromCache(alternatives).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
                    {
                        $@"{resettable}.reset();",
                        $@"{cppOptions.FromCache(alternatives).Name}(false, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1);",
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