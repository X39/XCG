﻿using System.Collections.Generic;
using System.Linq;

namespace XCG.Generators.Cpp.Extensive
{
    internal static class ExtMatch
    {
        /// <summary>
        /// Creates the <see cref="MethodDefinition"/> for a provided <paramref name="match"/>.
        /// </summary>
        /// <remarks>
        /// Match Methods always are of the following prototype:
        /// <code>bool function(bool is_can, type actual)</code>
        /// where <code>function</code> is the name of the match function and <code>type</code> is the calling structure type.
        /// </remarks>
        /// <param name="match"></param>
        /// <param name="cppOptions"></param>
        /// <param name="skip">The amount of match-tokens to skip.</param>
        /// <param name="typeName">The type the <paramref name="match"/> gets to capture things onto.</param>
        /// <returns></returns>
        public static MethodDefinition CreateMethodDefinition(this Parsing.Statements.Match match, CppOptions cppOptions, int skip, string typeName, string stateTypeName)
        {
            var ___localsCount = 0;
            string toUnique(string str) => string.Concat(str, (++___localsCount).ToString());
            // ToDo: Rewrite to use skip method too
            // Unique Variables
            var resettable = toUnique("resettable");



            var references = match.Matches.Cast<Parsing.Reference>().Skip(skip).ToArray();

            var matchName = string.Join("_", match.Matches.WhereIs<Parsing.Reference>().Select((q) => q.Refered switch
            {
                Parsing.Token token => token.Identifier,
                Parsing.Production production => production.Identifier,
                Parsing.LeftRecursive leftRecursive => leftRecursive.Identifier,
                _ => q.Text,
            }).Prepend("m")).Replace("-", string.Empty).Replace("@", string.Empty);
            var methodDefinition = new MethodDefinition(
                EType.Boolean,
                cppOptions.ToUnique(string.Concat(cppOptions.MethodsPrefix, matchName, "_")),
                new ArgImpl { Name = Constants.isCanVariable, Type = EType.Boolean },
                new ArgImpl { Name = Constants.classInstanceVariable, TypeString = typeName, ReferenceCount = 1 },
                new ArgImpl { Name = Constants.stateInstanceVariable, TypeString = stateTypeName, ReferenceCount = 1 },
                new ArgImpl { Name = Constants.depthVariable, Type = EType.SizeT }
            )
            {
                $@"resettable {resettable}(*this);"
            };

            // Check whether this can be matched
            foreach (var reference in references)
            {
                switch (reference.Refered)
                {
                    case Parsing.Token token:
                        {
                            var lengthVariable = toUnique("l");
                            var indexVariable = toUnique("i");
                            methodDefinition.Add($@"auto {lengthVariable} = {token.GetMethodName()}({Constants.depthVariable} + 1);");
                            methodDefinition.Add(new IfPart(IfPart.EIfScope.If, $@"{lengthVariable}.has_value()")
                            {
                                $@"for (auto {indexVariable} = {lengthVariable}.value(); {indexVariable} != 0; {indexVariable}--)",
                                new ScopePart
                                {
                                    "next();"
                                },
                                $@"skip();",
                            });
                        }
                        break;
                    case Parsing.Production production:
                        {
                            methodDefinition.Add(new IfPart(IfPart.EIfScope.If, string.Concat(production.ToCppCanMatchMethodName(cppOptions), $@"({Constants.depthVariable} + 1)"))
                            {
                                $@"skip();"
                            });
                        }
                        break;
                    case Parsing.LeftRecursive leftRecursive:
                        {
                            methodDefinition.Add(new IfPart(IfPart.EIfScope.If, string.Concat(leftRecursive.ToCppCanMatchMethodName(cppOptions), $@"({Constants.depthVariable} + 1)"))
                            {
                                $@"skip();"
                            });
                        }
                        break;
                }
                methodDefinition.Add(new IfPart(IfPart.EIfScope.Else, Constants.isCanVariable)
                {
                    $@"{resettable}.reset();",
                    new DebugPart { $@"trace(""Returning false on {methodDefinition.Name}"", {Constants.depthVariable});" },
                    new ReturnPart(EValueConstant.False),
                });
                methodDefinition.Add(new IfPart(IfPart.EIfScope.Else, null)
                {
                    $@"report(""Something moved wrong (todo: improve error messages)"", {Constants.depthVariable});",
                    new DebugPart { $@"trace(""Returning false on {methodDefinition.Name}"", {Constants.depthVariable});" },
                    new ReturnPart(EValueConstant.False),
                });
            }
            methodDefinition.Add(new IfPart(IfPart.EIfScope.If, $@"{Constants.isCanVariable}")
            {
                new DebugPart { $@"trace(""Returning true on {methodDefinition.Name}"", {Constants.depthVariable});" },
                new ReturnPart(EValueConstant.True)
            });
            methodDefinition.Add($@"{resettable}.reset();");

            // Handle actual matches
            foreach (var reference in references)
            {
                var valueVariable = toUnique("val");
                if (reference.IsCaptured)
                {
                    var captureDefinition = cppOptions.ClassCaptureDefinitionsMap.GetValueOrDefault(reference) ?? throw new FatalException();
                    var call = reference.Refered switch
                    {
                        // Match the different possible refered things into proper conditions
                        Parsing.Token token => string.Concat("create_token(", token.GetMethodName(), $@"({Constants.depthVariable} + 1).value(), ", cppOptions.TokenEnumName, "::", token.GetCppEnumName(), ")"),
                        Parsing.Production production => string.Concat(production.ToCppMatchMethodName(cppOptions), $@"({Constants.depthVariable} + 1)"),
                        Parsing.LeftRecursive leftRecursive => string.Concat(leftRecursive.ToCppMatchMethodName(cppOptions), $@"({Constants.depthVariable} + 1)"),
                        _ => throw new FatalException()
                    };
                    methodDefinition.Add(new VariableDefinition(EType.Auto, valueVariable, call));
                    if (captureDefinition.IsSingleHit)
                    {
                        methodDefinition.Add($"{Constants.classInstanceVariable}->{reference.CaptureName?.ToCppName() ?? throw new FatalException()} = {valueVariable};");
                    }
                    else
                    {
                        methodDefinition.Add($"{Constants.classInstanceVariable}->{reference.CaptureName?.ToCppName() ?? throw new FatalException()}.push_back({valueVariable});");
                    }
                }
                else
                {
                    switch (reference.Refered)
                    {
                        // Match the different possible refered things into proper conditions
                        case Parsing.Token token:
                            var localVar = toUnique("l");
                            methodDefinition.Add(string.Concat("auto ", localVar, " = ", token.GetMethodName(), $@"({Constants.depthVariable} + 1).value();"));

                            methodDefinition.Add($"for (;{localVar} != 0; {localVar}--)");
                            methodDefinition.Add(new ScopePart
                            {
                                "next();"
                            });
                            break;
                       case Parsing.Production production:
                            methodDefinition.Add(string.Concat(production.ToCppMatchMethodName(cppOptions), $@"({Constants.depthVariable} + 1);"));
                            break;
                       case Parsing.LeftRecursive leftRecursive:
                            methodDefinition.Add(string.Concat(leftRecursive.ToCppMatchMethodName(cppOptions), $@"({Constants.depthVariable} + 1);"));
                            break;
                       default: throw new FatalException();
                    }
                }
                methodDefinition.Add($@"skip();");
            }

            // Handle any following statement too
            methodDefinition.AddRange(match.Children.Handle(cppOptions, false, toUnique));

            methodDefinition.Add(new DebugPart { $@"trace(""Returning true on {methodDefinition.Name}"", {Constants.depthVariable});" });
            methodDefinition.Add(new ReturnPart(EValueConstant.True));
            return methodDefinition;
        }
    }
}
