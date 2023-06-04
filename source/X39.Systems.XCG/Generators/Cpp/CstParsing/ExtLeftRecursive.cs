using System.Collections.Generic;
using System.Linq;
using X39.Systems.XCG.Generators.Cpp.CodeGeneration;

namespace X39.Systems.XCG.Generators.Cpp.CstParsing;

internal static class ExtLeftRecursive
{
    public static string ToCppTypeName(this Parsing.LeftRecursive leftRecursive, CppOptions cppOptions, bool full)
    {
        return string.Concat(full ? cppOptions.RootClassName : string.Empty, cppOptions.TypePrefix, leftRecursive.Identifier.ToCppName());
    }
    public static string ToCppStateTypeName(this Parsing.LeftRecursive leftRecursive, CppOptions cppOptions, bool full)
    {
        return string.Concat(leftRecursive.ToCppTypeName(cppOptions, full), "_state");
    }
    public static string ToCppCanMatchMethodName(this Parsing.LeftRecursive leftRecursive, CppOptions cppOptions)
    {
        return string.Concat(cppOptions.MethodsPrefix, "lr_can_", leftRecursive.Identifier.ToCppName());
    }
    public static string ToCppMatchMethodName(this Parsing.LeftRecursive leftRecursive, CppOptions cppOptions)
    {
        return string.Concat(cppOptions.MethodsPrefix, "lr_match_", leftRecursive.Identifier.ToCppName());
    }
    public static IEnumerable<ICppPart> ToParts(this Parsing.LeftRecursive leftRecursive, CppOptions cppOptions)
    {
        var localsCount = 0;
        string ToUnique(string str) => string.Concat(str, (++localsCount).ToString());
        // Output matches
        var matches = leftRecursive.Children.Cast<Parsing.Statements.Match>().ToArray();
        var lastMatch = matches.Last();
        var cppTypeName = leftRecursive.ToCppTypeName(cppOptions, true);
        var cppStateTypeName = leftRecursive.ToCppStateTypeName(cppOptions, true);
        foreach (var match in matches)
        {
            if (match == lastMatch)
            {
                foreach (var yielded in match.PrepareStatementMethods(cppTypeName, cppStateTypeName, cppOptions))
                {
                    yield return yielded;
                }
                yield return cppOptions.FromCacheOrCreate(match, (_) => match.CreateMethodDefinition(cppOptions, 0, cppTypeName.ToCppSharedPtrType(), cppStateTypeName));
            }
            else
            {
                foreach (var yielded in match.PrepareStatementMethods(cppTypeName, cppStateTypeName, cppOptions))
                {
                    yield return yielded;
                }
                yield return cppOptions.FromCacheOrCreate(match, (_) => match.CreateMethodDefinition(cppOptions, 1, cppTypeName.ToCppSharedPtrType(), cppStateTypeName));
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
        var canMatchMethodDefinition = new MethodDefinition(EType.Boolean, leftRecursive.ToCppCanMatchMethodName(cppOptions),
            new ArgImpl { Name = Constants.DepthVariable, Type = EType.SizeT })
        {
            $@"resettable {resettable}(*this);",
            new VariableDefinition(new TypeImpl {  TypeString = leftRecursive.ToCppTypeName(cppOptions, true).ToCppSharedPtrType() }, Constants.ClassInstanceFakeVariable),
            new VariableDefinition(new TypeImpl {  TypeString = leftRecursive.ToCppStateTypeName(cppOptions, false) }, Constants.StateInstanceVariable),
            new IfPart(IfPart.EIfScope.If, $@"!{cppOptions.FromCache(lastMatch).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
            {
                new DebugPart { $@"trace(""Returning false on {leftRecursive.Identifier}"", {Constants.DepthVariable});" },
                new ReturnPart(EValueConstant.False),
            },
            whileScope
        };
        var isFirst = true;
        foreach (var match in matches.Take(matches.Length - 1))
        {
            whileScope.Add(new IfPart(isFirst, $"{cppOptions.FromCache(match).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)"));
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
        var matchMethodDefinition = new MethodDefinition(leftRecursive.ToCppTypeName(cppOptions, true).ToCppSharedPtrType(), leftRecursive.ToCppMatchMethodName(cppOptions),
            new ArgImpl { Name = Constants.DepthVariable, Type = EType.SizeT })
        {
            new VariableDefinition(EType.Auto, Constants.ClassInstanceVariable, leftRecursive.ToCppTypeName(cppOptions, true).ToCppSharedPtrMake()),
            new VariableDefinition(new TypeImpl {  TypeString = leftRecursive.ToCppTypeName(cppOptions, true).ToCppSharedPtrType() }, Constants.ClassInstanceFakeVariable),
            new VariableDefinition(new TypeImpl {  TypeString = leftRecursive.ToCppStateTypeName(cppOptions, false) }, Constants.StateInstanceVariable),
            new IfPart(IfPart.EIfScope.If, $@"!{cppOptions.FromCache(lastMatch).Name}(false, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
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
            whileScope.Add(new IfPart(isFirst, $"{cppOptions.FromCache(match).Name}(true, {Constants.ClassInstanceFakeVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
            {
                $@"{resettable}.reset();",
                new IfPart(IfPart.EIfScope.If, $"!{isFirstVariable}")
                {
                    new VariableDefinition(EType.Auto, tmpActualVariable, Constants.ClassInstanceVariable),
                    $@"{Constants.ClassInstanceVariable} = {leftRecursive.ToCppTypeName(cppOptions, true).ToCppSharedPtrMake()};",
                    $@"{Constants.ClassInstanceVariable}->{(lastMatch.Matches.First() as Parsing.Reference)?.CaptureName ?? throw new FatalException()} = {tmpActualVariable};",
                },
                $"{isFirstVariable} = false;",
                $"{cppOptions.FromCache(match).Name}(false, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1);",
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