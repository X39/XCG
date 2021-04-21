using System;
using System.Collections.Generic;
using System.Linq;

namespace XCG.Generators.Cpp.Extensive
{
    internal static class ExtLeftRecursive
    {
        public static string ToCppTypeName(this Parsing.LeftRecursive leftRecursive, CppOptions cppOptions, bool full)
        {
            return String.Concat(full ? cppOptions.RootClassName : String.Empty, cppOptions.TypePrefix, leftRecursive.Identifier.ToCppName());
        }
        public static string ToCppStateTypeName(this Parsing.LeftRecursive leftRecursive, CppOptions cppOptions, bool full)
        {
            return String.Concat(leftRecursive.ToCppTypeName(cppOptions, full), "_state");
        }
        public static string ToCppCanMatchMethodName(this Parsing.LeftRecursive leftRecursive, CppOptions cppOptions)
        {
            return String.Concat(cppOptions.MethodsPrefix, "lr_can_", leftRecursive.Identifier.ToCppName());
        }
        public static string ToCppMatchMethodName(this Parsing.LeftRecursive leftRecursive, CppOptions cppOptions)
        {
            return String.Concat(cppOptions.MethodsPrefix, "lr_match_", leftRecursive.Identifier.ToCppName());
        }
        public static IEnumerable<ICppPart> ToParts(this Parsing.LeftRecursive leftRecursive, CppOptions cppOptions)
        {
            int ___localsCount = 0;
            string toUnique(string str) => String.Concat(str, (++___localsCount).ToString());
            // Output matches
            var matches = leftRecursive.Statements.Cast<Parsing.Statements.Match>().ToArray();
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
                    yield return cppOptions.FromCacheOrCreate(match, (m) => match.CreateMethodDefinition(cppOptions, 0, cppTypeName.ToCppSharedPtrType(), cppStateTypeName));
                }
                else
                {
                    foreach (var yielded in match.PrepareStatementMethods(cppTypeName, cppStateTypeName, cppOptions))
                    {
                        yield return yielded;
                    }
                    yield return cppOptions.FromCacheOrCreate(match, (m) => match.CreateMethodDefinition(cppOptions, 1, cppTypeName.ToCppSharedPtrType(), cppStateTypeName));
                }
            }

            // Generate can method
            #region CanMatch method
            string? resetable = toUnique("resetable");
            var whileScope = new WhilePart
            {
                $@"skip();",
                $@"resetable {resetable}(*this);",
            };
            var canMatchMethodDefinition = new MethodDefinition(EType.Boolean, leftRecursive.ToCppCanMatchMethodName(cppOptions))
            {
                $@"resetable {resetable}(*this);",
                new VariableDefinition(new TypeImpl {  TypeString = leftRecursive.ToCppTypeName(cppOptions, true).ToCppSharedPtrType() }, Constants.classInstanceFakeVariable),
                new VariableDefinition(new TypeImpl {  TypeString = leftRecursive.ToCppStateTypeName(cppOptions, false) }, Constants.stateInstanceVariable),
                new IfPart(IfPart.EIfScope.If, $@"!{cppOptions.FromCache(lastMatch).Name}(true, {Constants.classInstanceFakeVariable}, {Constants.stateInstanceVariable})")
                {
                    new ReturnPart(EValueConstant.False),
                },
                whileScope
            };
            bool isFirst = true;
            foreach (var match in matches.Take(matches.Length - 1))
            {
                whileScope.Add(new IfPart(isFirst, $"{cppOptions.FromCache(match).Name}(true, {Constants.classInstanceFakeVariable}, {Constants.stateInstanceVariable})"));
                isFirst = false;
            }
            whileScope.Add(new IfPart(IfPart.EIfScope.Else, null)
            {
                new ReturnPart(EValueConstant.True)
            });

            yield return canMatchMethodDefinition;
            #endregion

            // Generate match method
            whileScope = new WhilePart
            {
                $@"skip();",
                $@"resetable {resetable}(*this);",
            };
            var isFirstVariable = toUnique($@"is_first");
            var tmpActualVariable = toUnique($@"tmp_{Constants.classInstanceVariable}");
            var matchMethodDefinition = new MethodDefinition(leftRecursive.ToCppTypeName(cppOptions, true).ToCppSharedPtrType(), leftRecursive.ToCppMatchMethodName(cppOptions))
            {
                new VariableDefinition(EType.Auto, Constants.classInstanceVariable, leftRecursive.ToCppTypeName(cppOptions, true).ToCppSharedPtrMake()),
                new VariableDefinition(new TypeImpl {  TypeString = leftRecursive.ToCppTypeName(cppOptions, true).ToCppSharedPtrType() }, Constants.classInstanceFakeVariable),
                new VariableDefinition(new TypeImpl {  TypeString = leftRecursive.ToCppStateTypeName(cppOptions, false) }, Constants.stateInstanceVariable),
                new IfPart(IfPart.EIfScope.If, $@"!{cppOptions.FromCache(lastMatch).Name}(false, {Constants.classInstanceVariable}, {Constants.stateInstanceVariable})")
                {
                    $@"report(""Something moved wrong (todo: improve error messages)"");",
                    new ReturnPart(EValueConstant.EmptyClosure),
                },
                $@"bool {isFirstVariable} = true;",
                whileScope
            };
            isFirst = true;
            foreach (var match in matches.Take(matches.Length - 1))
            {
                whileScope.Add(new IfPart(isFirst, $"{cppOptions.FromCache(match).Name}(true, {Constants.classInstanceFakeVariable}, {Constants.stateInstanceVariable})")
                {
                    $@"{resetable}.reset();",
                    new IfPart(IfPart.EIfScope.If, $"!{isFirstVariable}")
                    {
                        new VariableDefinition(EType.Auto, tmpActualVariable, Constants.classInstanceVariable),
                        $@"{Constants.classInstanceVariable} = {leftRecursive.ToCppTypeName(cppOptions, true).ToCppSharedPtrMake()};",
                        $@"{Constants.classInstanceVariable}->{(lastMatch.Parts.First() as Parsing.Reference)?.CaptureName ?? throw new FatalException()} = {tmpActualVariable};",
                    },
                    $"{isFirstVariable} = false;",
                    $"{cppOptions.FromCache(match).Name}(false, {Constants.classInstanceVariable}, {Constants.stateInstanceVariable});",
                });
                isFirst = false;
            }
            whileScope.Add("else");
            whileScope.Add(new ScopePart
            {
                $@"{resetable}.reset();",
                "break;",
            });
            matchMethodDefinition.Add($@"return {Constants.classInstanceVariable};");
            yield return matchMethodDefinition;
        }
    }
}
