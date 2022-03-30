using System.Collections.Generic;
using System.Linq;

namespace XCG.Generators.CSharp.CstParsing;

internal static class ExtLeftRecursive
{
    public static string ToCppTypeName(this Parsing.LeftRecursive leftRecursive, CSharpOptions cSharpOptions, bool full)
    {
        return string.Concat(full ? cSharpOptions.RootClassName : string.Empty, cSharpOptions.TypePrefix, leftRecursive.Identifier.ToCppName());
    }
    public static string ToCppStateTypeName(this Parsing.LeftRecursive leftRecursive, CSharpOptions cSharpOptions, bool full)
    {
        return string.Concat(leftRecursive.ToCppTypeName(cSharpOptions, full), "_state");
    }
    public static string ToCppCanMatchMethodName(this Parsing.LeftRecursive leftRecursive, CSharpOptions cSharpOptions)
    {
        return string.Concat(cSharpOptions.MethodsPrefix, "lr_can_", leftRecursive.Identifier.ToCppName());
    }
    public static string ToCppMatchMethodName(this Parsing.LeftRecursive leftRecursive, CSharpOptions cSharpOptions)
    {
        return string.Concat(cSharpOptions.MethodsPrefix, "lr_match_", leftRecursive.Identifier.ToCppName());
    }
    public static IEnumerable<ICppPart> ToParts(this Parsing.LeftRecursive leftRecursive, CSharpOptions cSharpOptions)
    {
        var localsCount = 0;
        string ToUnique(string str) => string.Concat(str, (++localsCount).ToString());
        // Output matches
        var matches = leftRecursive.Children.Cast<Parsing.Statements.Match>().ToArray();
        var lastMatch = matches.Last();
        var cppTypeName = leftRecursive.ToCppTypeName(cSharpOptions, true);
        var cppStateTypeName = leftRecursive.ToCppStateTypeName(cSharpOptions, true);
        foreach (var match in matches)
        {
            if (match == lastMatch)
            {
                foreach (var yielded in match.PrepareStatementMethods(cppTypeName, cppStateTypeName, cSharpOptions))
                {
                    yield return yielded;
                }
                yield return cSharpOptions.FromCacheOrCreate(match, (_) => match.CreateMethodDefinition(cSharpOptions, 0, cppTypeName.ToCppSharedPtrType(), cppStateTypeName));
            }
            else
            {
                foreach (var yielded in match.PrepareStatementMethods(cppTypeName, cppStateTypeName, cSharpOptions))
                {
                    yield return yielded;
                }
                yield return cSharpOptions.FromCacheOrCreate(match, (_) => match.CreateMethodDefinition(cSharpOptions, 1, cppTypeName.ToCppSharedPtrType(), cppStateTypeName));
            }
        }

        // Generate can method
        #region CanMatch method
        var resettable = ToUnique("resettable");
        var whileScope = new WhilePart
        {
            $@"skip();",
            $@"resettable {resettable}(*this);",
        };
        var canMatchMethodDefinition = new MethodDefinition(EType.Boolean, leftRecursive.ToCppCanMatchMethodName(cSharpOptions),
            new ArgImpl { Name = Constants.DepthVariable, Type = EType.SizeT })
        {
            $@"resettable {resettable}(*this);",
            new VariableDefinition(new TypeImpl {  TypeString = leftRecursive.ToCppTypeName(cSharpOptions, true).ToCppSharedPtrType() }, Constants.ClassInstanceFakeVariable),
            new VariableDefinition(new TypeImpl {  TypeString = leftRecursive.ToCppStateTypeName(cSharpOptions, false) }, Constants.StateInstanceVariable),
            new IfPart(IfPart.EIfScope.If, $@"!{cSharpOptions.FromCache(lastMatch).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
            {
                new DebugPart { $@"trace(""Returning false on {leftRecursive.Identifier}"", {Constants.DepthVariable});" },
                new ReturnPart(EValueConstant.False),
            },
            whileScope
        };
        var isFirst = true;
        foreach (var match in matches.Take(matches.Length - 1))
        {
            whileScope.Add(new IfPart(isFirst, $"{cSharpOptions.FromCache(match).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)"));
            isFirst = false;
        }
        whileScope.Add(new IfPart(IfPart.EIfScope.Else, null)
        {
            new DebugPart { $@"trace(""Returning true on {leftRecursive.Identifier}"", {Constants.DepthVariable});" },
            new ReturnPart(EValueConstant.True)
        });

        yield return canMatchMethodDefinition;
        #endregion

        // Generate match method
        whileScope = new WhilePart
        {
            $@"skip();",
            $@"resettable {resettable}(*this);",
        };
        var isFirstVariable = ToUnique($@"is_first");
        var tmpActualVariable = ToUnique($@"tmp_{Constants.ClassInstanceVariable}");
        var matchMethodDefinition = new MethodDefinition(leftRecursive.ToCppTypeName(cSharpOptions, true).ToCppSharedPtrType(), leftRecursive.ToCppMatchMethodName(cSharpOptions),
            new ArgImpl { Name = Constants.DepthVariable, Type = EType.SizeT })
        {
            new VariableDefinition(EType.Auto, Constants.ClassInstanceVariable, leftRecursive.ToCppTypeName(cSharpOptions, true).ToCppSharedPtrMake()),
            new VariableDefinition(new TypeImpl {  TypeString = leftRecursive.ToCppTypeName(cSharpOptions, true).ToCppSharedPtrType() }, Constants.ClassInstanceFakeVariable),
            new VariableDefinition(new TypeImpl {  TypeString = leftRecursive.ToCppStateTypeName(cSharpOptions, false) }, Constants.StateInstanceVariable),
            new IfPart(IfPart.EIfScope.If, $@"!{cSharpOptions.FromCache(lastMatch).Name}(false, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
            {
                $@"report(""Something moved wrong (todo: improve error messages)"", {Constants.DepthVariable});",
                new DebugPart { $@"trace(""Returning EmptyClosure on {leftRecursive.Identifier}"", {Constants.DepthVariable});" },
                new ReturnPart(EValueConstant.EmptyClosure),
            },
            $@"bool {isFirstVariable} = true;",
            whileScope
        };
        isFirst = true;
        foreach (var match in matches.Take(matches.Length - 1))
        {
            whileScope.Add(new IfPart(isFirst, $"{cSharpOptions.FromCache(match).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
            {
                $@"{resettable}.reset();",
                new IfPart(IfPart.EIfScope.If, $"!{isFirstVariable}")
                {
                    new VariableDefinition(EType.Auto, tmpActualVariable, Constants.ClassInstanceVariable),
                    $@"{Constants.ClassInstanceVariable} = {leftRecursive.ToCppTypeName(cSharpOptions, true).ToCppSharedPtrMake()};",
                    $@"{Constants.ClassInstanceVariable}->{(lastMatch.Matches.First() as Parsing.Reference)?.CaptureName ?? throw new FatalException()} = {tmpActualVariable};",
                },
                $"{isFirstVariable} = false;",
                $"{cSharpOptions.FromCache(match).Name}(false, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1);",
            });
            isFirst = false;
        }
        whileScope.Add("else");
        whileScope.Add(new ScopePart
        {
            $@"{resettable}.reset();",
            "break;",
        });
        matchMethodDefinition.Add($@"return {Constants.ClassInstanceVariable};");
        yield return matchMethodDefinition;
    }
}