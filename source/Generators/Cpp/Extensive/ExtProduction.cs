using System;
using System.Collections.Generic;

namespace XCG.Generators.Cpp.Extensive
{
    internal static class ExtProduction
    {
        public static string ToCppTypeName(this Parsing.Production production, CppOptions cppOptions, bool full)
        {
            return String.Concat(full ? cppOptions.RootClassName : String.Empty, cppOptions.TypePrefix, production.Identifier.ToCppName());
        }
        public static string ToCppStateTypeName(this Parsing.Production production, CppOptions cppOptions, bool full)
        {
            return String.Concat(production.ToCppTypeName(cppOptions, full), "_state");
        }
        public static string ToCppCanMatchMethodName(this Parsing.Production production, CppOptions cppOptions)
        {
            return String.Concat(cppOptions.MethodsPrefix, "p_can_", production.Identifier.ToCppName());
        }
        public static string ToCppMatchMethodName(this Parsing.Production production, CppOptions cppOptions)
        {
            return String.Concat(cppOptions.MethodsPrefix, "p_match_", production.Identifier.ToCppName());
        }
        public static IEnumerable<ICppPart> ToParts(this Parsing.Production production, CppOptions cppOptions)
        {
            int ___localsCount = 0;
            string toUnique(string str) => String.Concat(str, (++___localsCount).ToString());
            // Output matches
            foreach (var it in production.PrepareStatementMethods(production.ToCppTypeName(cppOptions, true), production.ToCppStateTypeName(cppOptions, true), cppOptions))
            {
                yield return it;
            }

            // Generate can method
            string? resetable = toUnique("resetable");
            var canMatchMethodDefinition = new MethodDefinition(EType.Boolean, production.ToCppCanMatchMethodName(cppOptions),
                new ArgImpl { Name = Constants.depthVariable, Type = EType.SizeT })
            {
                $@"resetable {resetable}(*this);",
                new VariableDefinition(new TypeImpl {  TypeString = production.ToCppTypeName(cppOptions, true).ToCppSharedPtrType() }, Constants.classInstanceFakeVariable),
                new VariableDefinition(new TypeImpl {  TypeString = production.ToCppStateTypeName(cppOptions, false) }, Constants.stateInstanceVariable),
            };
            bool isFirst = true;
            foreach (var statement in production.Children)
            {
                switch (statement)
                {
                    case Parsing.Statements.Match match:
                        canMatchMethodDefinition.Add(new IfPart(isIf: isFirst, $@"!{cppOptions.FromCache(match).Name}(true, {Constants.classInstanceFakeVariable}, {Constants.stateInstanceVariable}, {Constants.depthVariable} + 1)")
                        {
                            $@"{resetable}.reset();",
                            new DebugPart { $@"trace(""Returning false on {production.Identifier}"", {Constants.depthVariable});" },
                            new ReturnPart(EValueConstant.False),
                        });
                        break;
                    case Parsing.Statements.Alternatives alternatives:
                        canMatchMethodDefinition.Add(new IfPart(isIf: isFirst, $@"!{cppOptions.FromCache(alternatives).Name}(true, {Constants.classInstanceFakeVariable}, {Constants.stateInstanceVariable}, {Constants.depthVariable} + 1)")
                        {
                            $@"{resetable}.reset();",
                            new DebugPart { $@"trace(""Returning false on {production.Identifier}"", {Constants.depthVariable});" },
                            new ReturnPart(EValueConstant.False),
                        });
                        break;
                    case Parsing.Statements.If @if:
                        canMatchMethodDefinition.Add(new IfPart(isIf: isFirst, $@"!{cppOptions.FromCache(@if).Name}(true, {Constants.classInstanceFakeVariable}, {Constants.stateInstanceVariable}, {Constants.depthVariable} + 1)")
                        {
                            $@"{resetable}.reset();",
                            new DebugPart { $@"trace(""Returning false on {production.Identifier}"", {Constants.depthVariable});" },
                            new ReturnPart(EValueConstant.False),
                        });
                        break;
                    case Parsing.Statements.While @while:
                        canMatchMethodDefinition.Add(new IfPart(isIf: isFirst, $@"!{cppOptions.FromCache(@while).Name}(true, {Constants.classInstanceFakeVariable}, {Constants.stateInstanceVariable}, {Constants.depthVariable} + 1)")
                        {
                            $@"{resetable}.reset();",
                            new DebugPart { $@"trace(""Returning false on {production.Identifier}"", {Constants.depthVariable});" },
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
            canMatchMethodDefinition.Add(new DebugPart { $@"trace(""Returning true on {production.Identifier}"", {Constants.depthVariable});" });
            canMatchMethodDefinition.Add(new ReturnPart(EValueConstant.True));
            yield return canMatchMethodDefinition;

            // Generate match method
            var matchMethodDefinition = new MethodDefinition(production.ToCppTypeName(cppOptions, true).ToCppSharedPtrType(), production.ToCppMatchMethodName(cppOptions),
                new ArgImpl { Name = Constants.depthVariable, Type = EType.SizeT })
            {
                new VariableDefinition(EType.Auto, Constants.classInstanceVariable, production.ToCppTypeName(cppOptions, true).ToCppSharedPtrMake()),
                new VariableDefinition(new TypeImpl {  TypeString = production.ToCppTypeName(cppOptions, true).ToCppSharedPtrType() }, Constants.classInstanceFakeVariable),
                new VariableDefinition(new TypeImpl {  TypeString = production.ToCppStateTypeName(cppOptions, false) }, Constants.stateInstanceVariable),
            };
            isFirst = true;
            foreach (var statement in production.Children)
            {
                resetable = toUnique("resetable");
                matchMethodDefinition.Add($@"resetable {resetable}(*this);");
                switch (statement)
                {
                    case Parsing.Statements.Match match:
                        matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.If, $@"{cppOptions.FromCache(match).Name}(true, {Constants.classInstanceFakeVariable}, {Constants.stateInstanceVariable}, {Constants.depthVariable} + 1)")
                        {
                            $@"{resetable}.reset();",
                            $@"{cppOptions.FromCache(match).Name}(false, {Constants.classInstanceVariable}, {Constants.stateInstanceVariable}, {Constants.depthVariable} + 1);",
                        });
                        matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.Else, null)
                        {
                            $@"report(""Something moved wrong (todo: improve error messages)"", {Constants.depthVariable});",
                        });
                        break;
                    case Parsing.Statements.While @while:
                        matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.If, $@"{cppOptions.FromCache(@while).Name}(true, {Constants.classInstanceFakeVariable}, {Constants.stateInstanceVariable}, {Constants.depthVariable} + 1)")
                        {
                            $@"{resetable}.reset();",
                            $@"{cppOptions.FromCache(@while).Name}(false, {Constants.classInstanceVariable}, {Constants.stateInstanceVariable}, {Constants.depthVariable} + 1);",
                        });
                        matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.Else, null)
                        {
                            $@"report(""Something moved wrong (todo: improve error messages)"", {Constants.depthVariable});",
                        });
                        break;
                    case Parsing.Statements.If @if:
                        matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.If, $@"{cppOptions.FromCache(@if).Name}(true, {Constants.classInstanceFakeVariable}, {Constants.stateInstanceVariable}, {Constants.depthVariable} + 1)")
                        {
                            $@"{resetable}.reset();",
                            $@"{cppOptions.FromCache(@if).Name}(false, {Constants.classInstanceVariable}, {Constants.stateInstanceVariable}, {Constants.depthVariable} + 1);",
                        });
                        matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.Else, null)
                        {
                            $@"report(""Something moved wrong (todo: improve error messages)"", {Constants.depthVariable});",
                        });
                        break;
                    case Parsing.Statements.Alternatives alternatives:
                        matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.If, $@"{cppOptions.FromCache(alternatives).Name}(true, {Constants.classInstanceFakeVariable}, {Constants.stateInstanceVariable}, {Constants.depthVariable} + 1)")
                        {
                            $@"{resetable}.reset();",
                            $@"{cppOptions.FromCache(alternatives).Name}(false, {Constants.classInstanceVariable}, {Constants.stateInstanceVariable}, {Constants.depthVariable} + 1);",
                        });
                        matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.Else, null)
                        {
                            $@"report(""Something moved wrong (todo: improve error messages)"", {Constants.depthVariable});",
                        });
                        break;
                    case Parsing.Statements.Set:
                        continue;
                    default:
                        throw new NotImplementedException();
                }
                isFirst = false;
            }
            matchMethodDefinition.Add($@"return {Constants.classInstanceVariable};");
            yield return matchMethodDefinition;
        }
    }
}
