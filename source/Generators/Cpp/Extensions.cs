using System;
using System.Collections.Generic;
using System.Linq;

namespace XCG.Generators.Cpp
{
    internal static class Extensions
    {
        private const string isCanVariable = "is_can";
        private const string classInstanceVariable = "actual";
        public static string ToCppSharedPtrType(this string str)
        {
            return String.Concat("std::shared_ptr<", str, ">");
        }
        public static string ToCppSharedPtrMake(this string str, params string[] args)
        {
            return String.Concat("std::make_shared<", str, ">(", String.Join(", ", args), ")");
        }
        public static string ToCppName(this string str)
        {
            return String.Concat(str.Replace('-', '_').Replace('@', '_').ToLower());
        }
        public static string GetMethodName(this Parsing.Token token)
        {
            return String.Concat("token_", token.Identifier.Replace('-', '_').Replace('@', '_').ToLower());
        }
        public static string GetCppEnumName(this Parsing.Token token)
        {
            return String.Concat(token.Identifier.Replace('-', '_').Replace('@', '_').ToUpper());
        }
        public static string ToCppTypeName(this Parsing.Token token, CppOptions cppOptions, bool full)
        {
            return String.Concat(full ? cppOptions.RootClassName : String.Empty, cppOptions.TypePrefix, cppOptions.TokenName);
        }

        public static string ToCppTypeName(this Parsing.Production production, CppOptions cppOptions, bool full)
        {
            return String.Concat(full ? cppOptions.RootClassName : String.Empty, cppOptions.TypePrefix, production.Identifier.ToCppName());
        }
        public static string ToCppCanMatchMethodName(this Parsing.Production production, CppOptions cppOptions)
        {
            return String.Concat(cppOptions.MethodsPrefix, "p_can_", production.Identifier.ToCppName());
        }
        public static string ToCppMatchMethodName(this Parsing.Production production, CppOptions cppOptions)
        {
            return String.Concat(cppOptions.MethodsPrefix, "p_match_", production.Identifier.ToCppName());
        }

        public static string ToCppTypeName(this Parsing.LeftRecursive leftRecursive, CppOptions cppOptions, bool full)
        {
            return String.Concat(full ? cppOptions.RootClassName : String.Empty, cppOptions.TypePrefix, leftRecursive.Identifier.ToCppName());
        }
        public static string ToCppCanMatchMethodName(this Parsing.LeftRecursive leftRecursive, CppOptions cppOptions)
        {
            return String.Concat(cppOptions.MethodsPrefix, "lr_can_", leftRecursive.Identifier.ToCppName());
        }
        public static string ToCppMatchMethodName(this Parsing.LeftRecursive leftRecursive, CppOptions cppOptions)
        {
            return String.Concat(cppOptions.MethodsPrefix, "lr_match_", leftRecursive.Identifier.ToCppName());
        }


        public static IEnumerable<ICppPart> ToParts(this Parsing.Token token, CppOptions cppOptions)
        {
            int ___localsCount = 0;
            string toUnique(string str) => String.Concat(str, (++___localsCount).ToString());
            string? resetable = toUnique("resetable");
            var methodDefinition = new MethodDefinition(EType.OptionalSizeT, token.GetMethodName())
            {
                new FullBody { $@"resetable {resetable}(*this);" }
            };

            foreach (var statement in token.Statements)
            {
                if (statement is Parsing.TokenStatements.Require require)
                {
                    var scopePart = new ScopePart { new VariableDefinition(EType.SizeT, "count", "0") };
                    methodDefinition.Add(scopePart);
                    var localLoop = require.Range.To != Int32.MaxValue ? new WhileLoopPart($"current() != '\\0' && count < {require.Range.To}") : new WhileLoopPart("current() != '\\0'");
                    scopePart.Add(localLoop);
                    int localsCount = 0;
                    bool isFirst = true;
                    foreach (var part in require.Parts)
                    {
                        if (part is Parsing.Word word)
                        {
                            if (word.Text.Length > 1)
                            {
                                localLoop.Add(new FullBody
                                {
                                    $@"const char* l{++localsCount} = ""{word.Text.Replace("\"", "\\\"")}"";",
                                    $@"if (m_contents.length() - m_offset < {word.Text.Length} &&",
                                    $@"    std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + {word.Text.Length}, l{localsCount}, l{localsCount} + {word.Text.Length}))",
                                    $@"{{",
                                    $@"    count++;",
                                    $@"    for (size_t i = 0; i < {word.Text.Length}; i++)",
                                    $@"    {{",
                                    $@"        next();",
                                    $@"    }}",
                                    $@"    continue;",
                                    $@"}}",
                                });
                            }
                            else
                            {
                                localLoop.Add(new FullBody
                                {
                                    $@"if (current() == '{word.Text.First()}')",
                                    $@"{{",
                                    $@"    count++;",
                                    $@"    next();",
                                    $@"    continue;",
                                    $@"}}",
                                });
                            }
                        }
                        else if (part is Parsing.CharacterRange range)
                        {
                            localLoop.Add(new IfPart(isFirst, $@"'{range.Start}' <= current() && current() <= '{range.End}'")
                            {
                                $@"count++;",
                                $@"next();",
                                $@"continue;",
                            });
                        }
                        else if (part is Parsing.Reference reference)
                        {
                            if (reference.Refered is Parsing.Token referedToken)
                            {
                                localLoop.Add($@"auto l{++localsCount} = {referedToken.GetMethodName()}();");
                                localLoop.Add(new IfPart(IfPart.EIfScope.If, $@"l{localsCount}.has_value()")
                                {
                                    $@"count++;",
                                    $@"for (size_t i = 0; i < l{localsCount}; i++)",
                                    $@"{{",
                                    $@"    next();",
                                    $@"}}",
                                    $@"continue;",
                                });
                            }
                            else
                            {
                                throw new FatalException("Unimplemented Require Part");
                            }
                        }
                        else
                        {
                            throw new FatalException("Unimplemented Require Part");
                        }
                        isFirst = false;
                    }
                    localLoop.Add(new FullBody { $@"break;" });
                    if (require.Range.From > 0)
                    {
                        scopePart.Add(new IfPart(IfPart.EIfScope.If, $@"count < {require.Range.From}")
                        {
                            $@"{resetable}.reset();",
                            $@"return {{}};",
                        });
                    }
                }
                else if (statement is Parsing.TokenStatements.Backtrack backtrack)
                {
                    // ToDo: Implement backtracking
                    throw new NotImplementedException();
                }
                else
                {
                    throw new FatalException("Unimplemented TokenStatement");
                }
            }

            var resultVariable = cppOptions.ToUnique("resultVariable");
            methodDefinition.Add(new FullBody {
                $@"auto {resultVariable} = m_offset - {resetable}.m_offset;",
                $@"{resetable}.reset();",
                $@"return {resultVariable};",
            });
            return new[] { methodDefinition };
        }

        public static ClassDefinition GetClassDefinition(Parsing.IStatement statement, CppOptions cppOptions)
        {
            var captureModifyingSets = statement.FindChildren<Parsing.Statements.Set>()
                .Where((q) => q.ActiveScope == Parsing.EActiveScope.capture)
                .ToArray();
            var captureContainingReferences = statement.FindChildren<Parsing.Statements.Match>()
                .SelectMany((q) => q.Parts)
                .Where((q) => q is Parsing.Reference)
                .Cast<Parsing.Reference>()
                .Where((q) => q.IsCaptured)
                .ToArray();
            var captureDefinitions = new Dictionary<string, CaptureDefinition>();
            foreach (var captureModifyingSet in captureModifyingSets)
            {
                string? captureName = captureModifyingSet.Property.ToCppName();
                if (!captureDefinitions.TryGetValue(captureName, out var captureDefinition))
                {
                    captureDefinition = new CaptureDefinition(captureName);
                    captureDefinitions[captureName] = captureDefinition;
                }
                var typeImpl = new TypeImpl
                {
                    Type = captureModifyingSet.Statements.First() switch
                    {
                        Parsing.Expressions.CreateNewBoolean => EType.OptionalBoolean,
                        Parsing.Expressions.Bool => EType.OptionalBoolean,
                        Parsing.Expressions.CreateNewCharacter => EType.OptionalChar,
                        Parsing.Expressions.Character => EType.OptionalChar,
                        Parsing.Expressions.CreateNewNumber => EType.OptionalDouble,
                        Parsing.Expressions.Number => EType.OptionalDouble,
                        _ => throw new FatalException()
                    }
                };
                if (!captureDefinition.Types.Contains(typeImpl))
                {
                    captureDefinition.Types.Add(typeImpl);
                }
            }
            foreach (var captureContainingReference in captureContainingReferences)
            {
                TypeImpl typeImpl = captureContainingReference.Refered switch
                {
                    Parsing.Token token => new TypeImpl { Type = EType.Token },
                    Parsing.Production production => new TypeImpl { TypeString = production.ToCppTypeName(cppOptions, false).ToCppSharedPtrType() },
                    Parsing.LeftRecursive leftRecursion => new TypeImpl { TypeString = leftRecursion.ToCppTypeName(cppOptions, false).ToCppSharedPtrType() },
                    _ => throw new FatalException()
                };
                string? captureName = captureContainingReference.CaptureName ?? throw new FatalException();
                if (!captureDefinitions.TryGetValue(captureName, out var captureDefinition))
                {
                    captureDefinition = new CaptureDefinition(captureName);
                    captureDefinitions[captureName] = captureDefinition;
                }
                if (!captureDefinition.Types.Contains(typeImpl))
                {
                    captureDefinition.Types.Add(typeImpl);
                }
            }

            return new ClassDefinition(statement switch
            {
                Parsing.Token token => token.ToCppTypeName(cppOptions, false),
                Parsing.Production production => production.ToCppTypeName(cppOptions, false),
                Parsing.LeftRecursive leftRecursion => leftRecursion.ToCppTypeName(cppOptions, false),
                _ => throw new FatalException()
            })
            {
                PublicParts = new List<ICppPart>(captureDefinitions.Values)
            };
        }
        private static IEnumerable<ICppPart> PrepareStatementMethods(Parsing.IStatement statement, string cppTypeName, CppOptions cppOptions)
        {
            // Output matches
            foreach (var it in statement.Statements)
            {
                switch (it)
                {
                    case Parsing.Statements.Alternatives alternatives:
                        foreach (var yielded in PrepareStatementMethods(alternatives, cppTypeName, cppOptions))
                        {
                            yield return yielded;
                        }
                        yield return cppOptions.FromCacheOrCreate(it, (m) => alternatives.CreateMethodDefinition(cppOptions, cppTypeName.ToCppSharedPtrType()));
                        break;
                    case Parsing.Statements.Match match:
                        foreach (var yielded in PrepareStatementMethods(match, cppTypeName, cppOptions))
                        {
                            yield return yielded;
                        }
                        yield return cppOptions.FromCacheOrCreate(it, (m) => match.CreateMethodDefinition(cppOptions, 0, cppTypeName.ToCppSharedPtrType()));
                        break;
                    case Parsing.Statements.Set set:
                        break;
                    default:
                        throw new NotImplementedException();
                }
            }
        }
        public static IEnumerable<ICppPart> ToParts(this Parsing.Production production, CppOptions cppOptions)
        {
            int ___localsCount = 0;
            string toUnique(string str) => String.Concat(str, (++___localsCount).ToString());
            // Output matches
            foreach (var it in PrepareStatementMethods(production, production.ToCppTypeName(cppOptions, true), cppOptions))
            {
                yield return it;
            }

            // Generate can method
            string? resetable = toUnique("resetable");
            var canMatchMethodDefinition = new MethodDefinition(EType.Boolean, production.ToCppCanMatchMethodName(cppOptions))
            {
                $@"resetable {resetable}(*this);",
            };
            bool isFirst = true;
            foreach (var statement in production.Statements)
            {
                switch (statement)
                {
                    case Parsing.Statements.Match match:
                        canMatchMethodDefinition.Add(new IfPart(isIf: isFirst, $@"!{cppOptions.FromCache(match).Name}(true, {{}})")
                        {
                            $@"{resetable}.reset();",
                            $@"return false;",
                        });
                        break;
                    case Parsing.Statements.Alternatives alternatives:
                        canMatchMethodDefinition.Add(new IfPart(isIf: isFirst, $@"!{cppOptions.FromCache(alternatives).Name}(true, {{}})")
                        {
                            $@"{resetable}.reset();",
                            $@"return false;",
                        });
                        break;
                    case Parsing.Statements.Set:
                        break;
                    default:
                        throw new NotImplementedException();
                }
                isFirst = false;
            }
            canMatchMethodDefinition.Add($@"return true;");
            yield return canMatchMethodDefinition;

            // Generate match method
            var matchMethodDefinition = new MethodDefinition(production.ToCppTypeName(cppOptions, true).ToCppSharedPtrType(), production.ToCppMatchMethodName(cppOptions))
            {
                $@"auto {classInstanceVariable} = {production.ToCppTypeName(cppOptions, true).ToCppSharedPtrMake()};",
            };
            isFirst = true;
            foreach (var statement in production.Statements)
            {
                resetable = toUnique("resetable");
                matchMethodDefinition.Add($@"resetable {resetable}(*this);");
                switch (statement)
                {
                    case Parsing.Statements.Match match:
                        matchMethodDefinition.Add(new IfPart(isIf: isFirst, $@"{cppOptions.FromCache(match).Name}(true, {{}})")
                        {
                            $@"{resetable}.reset();",
                            $@"{cppOptions.FromCache(match).Name}(false, {classInstanceVariable});",
                        });
                        matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.Else, null)
                        {
                            $@"report(""Something moved wrong (todo: improve error messages)"");",
                        });
                        break;
                    case Parsing.Statements.Alternatives alternatives:
                        matchMethodDefinition.Add(new IfPart(isIf: isFirst, $@"{cppOptions.FromCache(alternatives).Name}(true, {{}})")
                        {
                            $@"{resetable}.reset();",
                            $@"{cppOptions.FromCache(alternatives).Name}(false, {classInstanceVariable});",
                        });
                        matchMethodDefinition.Add(new IfPart(IfPart.EIfScope.Else, null)
                        {
                            $@"report(""Something moved wrong (todo: improve error messages)"");",
                        });
                        break;
                    case Parsing.Statements.Set:
                        break;
                    default:
                        throw new NotImplementedException();
                }
                isFirst = false;
            }
            matchMethodDefinition.Add($@"return {classInstanceVariable};");
            yield return matchMethodDefinition;
        }
        public static IEnumerable<ICppPart> ToParts(this Parsing.LeftRecursive leftRecursive, CppOptions cppOptions)
        {
            int ___localsCount = 0;
            string toUnique(string str) => String.Concat(str, (++___localsCount).ToString());
            // Output matches
            var matches = leftRecursive.Statements.Cast<Parsing.Statements.Match>().ToArray();
            var lastMatch = matches.Last();
            var cppTypeName = leftRecursive.ToCppTypeName(cppOptions, true);
            foreach (var match in matches)
            {
                if (match == lastMatch)
                {
                    foreach (var yielded in PrepareStatementMethods(match, cppTypeName, cppOptions))
                    {
                        yield return yielded;
                    }
                    yield return cppOptions.FromCacheOrCreate(match, (m) => match.CreateMethodDefinition(cppOptions, 0, cppTypeName.ToCppSharedPtrType()));
                }
                else
                {
                    foreach (var yielded in PrepareStatementMethods(match, cppTypeName, cppOptions))
                    {
                        yield return yielded;
                    }
                    yield return cppOptions.FromCacheOrCreate(match, (m) => match.CreateMethodDefinition(cppOptions, 1, cppTypeName.ToCppSharedPtrType()));
                }
            }

            // Generate can method
            #region CanMatch method
            string? resetable = toUnique("resetable");
            var whileScope = new ScopePart
            {
                $@"skip();",
                $@"resetable {resetable}(*this);",
            };
            var canMatchMethodDefinition = new MethodDefinition(EType.Boolean, leftRecursive.ToCppCanMatchMethodName(cppOptions))
            {
                $@"resetable {resetable}(*this);",
                new IfPart(IfPart.EIfScope.If, $@"!{cppOptions.FromCache(lastMatch).Name}(true, {{}})")
                {
                    $@"return false;",
                },
                $@"while (true)",
                whileScope
            };
            bool isFirst = true;
            foreach (var match in matches.Take(matches.Length - 1))
            {
                whileScope.Add(new IfPart(isFirst, $"{cppOptions.FromCache(match).Name}(true, {{}})"));
                isFirst = false;
            }
            whileScope.Add("else");
            whileScope.Add(new ScopePart
            {
                $@"return true;"
            });

            yield return canMatchMethodDefinition;
            #endregion

            // Generate match method
            whileScope = new ScopePart
            {
                $@"skip();",
                $@"resetable {resetable}(*this);",
            };
            var isFirstVariable = toUnique($@"is_first");
            var tmpActualVariable = toUnique($@"tmp_{classInstanceVariable}");
            var matchMethodDefinition = new MethodDefinition(leftRecursive.ToCppTypeName(cppOptions, true).ToCppSharedPtrType(), leftRecursive.ToCppMatchMethodName(cppOptions))
            {
                $@"auto {classInstanceVariable} = {leftRecursive.ToCppTypeName(cppOptions, true).ToCppSharedPtrMake()};",
                new IfPart(IfPart.EIfScope.If, $@"!{cppOptions.FromCache(lastMatch).Name}(false, {classInstanceVariable})")
                {
                    $@"report(""Something moved wrong (todo: improve error messages)"");",
                    $@"return {{}};",
                },
                $@"bool {isFirstVariable} = true;",
                $@"while (true)",
                whileScope
            };
            isFirst = true;
            foreach (var match in matches.Take(matches.Length - 1))
            {
                whileScope.Add(new IfPart(isFirst, $"{cppOptions.FromCache(match).Name}(true, {{}})")
                {
                    $@"{resetable}.reset();",
                    new IfPart(IfPart.EIfScope.If, $"!{isFirstVariable}")
                    {
                        $@"auto {tmpActualVariable} = {classInstanceVariable};",
                        $@"{classInstanceVariable} = {leftRecursive.ToCppTypeName(cppOptions, true).ToCppSharedPtrMake()};",
                        $@"{classInstanceVariable}->{(lastMatch.Parts.First() as Parsing.Reference)?.CaptureName ?? throw new FatalException()} = {tmpActualVariable};",
                    },
                    $"{isFirstVariable} = false;",
                    $"{cppOptions.FromCache(match).Name}(false, {classInstanceVariable});",
                });
                isFirst = false;
            }
            whileScope.Add("else");
            whileScope.Add(new ScopePart
            {
                $@"{resetable}.reset();",
                "break;",
            });
            matchMethodDefinition.Add($@"return {classInstanceVariable};");
            yield return matchMethodDefinition;
        }
        /// <summary>
        /// Receives the <see cref="ICppPart"/> for the provided <paramref name="match"/>.
        /// If <paramref name="isCanMethod"/> is true, the match will only check wether it can be matched,
        /// not generating any code to actually match.
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
        public static MethodDefinition CreateMethodDefinition(this Parsing.Statements.Match match, CppOptions cppOptions, int skip, string typeName)
        {
            int ___localsCount = 0;
            string toUnique(string str) => String.Concat(str, (++___localsCount).ToString());
            // ToDo: Rewrite to use skip method too
            // Unique Variables
            string? resetable = toUnique("resetable");



            var references = match.Parts.Cast<Parsing.Reference>().Skip(skip).ToArray();

            var matchName = String.Join("_", match.Parts.WhereIs<Parsing.Reference>().Select((q) => q.Refered switch
            {
                Parsing.Token token => token.Identifier,
                Parsing.Production production => production.Identifier,
                Parsing.LeftRecursive leftRecursive => leftRecursive.Identifier,
                _ => q.Text,
            }).Prepend("m")).Replace("-", String.Empty).Replace("@", String.Empty);
            var methodDefinition = new MethodDefinition(
                EType.Boolean,
                cppOptions.ToUnique(String.Concat(cppOptions.MethodsPrefix, matchName, "_")),
                new ArgImpl { Name = isCanVariable, Type = EType.Boolean },
                new ArgImpl { Name = classInstanceVariable, TypeString = typeName }
            )
            {
                $@"resetable {resetable}(*this);"
            };

            // Check wether this can be matched
            foreach (var reference in references)
            {
                switch (reference.Refered)
                {
                    case Parsing.Token token:
                        {
                            var lengthVariable = toUnique("l");
                            var indexVariable = toUnique("i");
                            methodDefinition.Add($@"auto {lengthVariable} = {token.GetMethodName()}();");
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
                            methodDefinition.Add(new IfPart(IfPart.EIfScope.If, String.Concat(production.ToCppCanMatchMethodName(cppOptions), "()"))
                            {
                                $@"skip();"
                            });
                        }
                        break;
                    case Parsing.LeftRecursive leftRecursive:
                        {
                            methodDefinition.Add(new IfPart(IfPart.EIfScope.If, String.Concat(leftRecursive.ToCppCanMatchMethodName(cppOptions), "()"))
                            {
                                $@"skip();"
                            });
                        }
                        break;
                }
                methodDefinition.Add(new IfPart(IfPart.EIfScope.Else, isCanVariable)
                {
                    $@"{resetable}.reset();",
                    $@"return false;",
                });
                methodDefinition.Add(new IfPart(IfPart.EIfScope.Else, null)
                {
                    $@"report(""Something moved wrong (todo: improve error messages)"");",
                    $@"return false;",
                });
            }
            methodDefinition.Add(new IfPart(IfPart.EIfScope.If, $@"{isCanVariable}")
            {
                "return true;"
            });
            methodDefinition.Add($@"{resetable}.reset();");

            // Handle actual matches
            foreach (var reference in references)
            {
                string? valueVariable = toUnique("val");
                if (reference.IsCaptured)
                {
                    string? call = reference.Refered switch
                    {
                        // Match the different possible refered things into proper conditions
                        Parsing.Token token => String.Concat("create_token(", token.GetMethodName(), "().value(), ", cppOptions.TokenEnumName, "::", token.GetCppEnumName(), ")"),
                        Parsing.Production production => String.Concat(production.ToCppMatchMethodName(cppOptions), "()"),
                        Parsing.LeftRecursive leftRecursive => String.Concat(leftRecursive.ToCppMatchMethodName(cppOptions), "()"),
                        _ => throw new FatalException()
                    };
                    methodDefinition.Add(new FullBody
                    {
                        $"auto {valueVariable} = {call};",
                        $"{classInstanceVariable}->{reference.CaptureName ?? throw new FatalException()} = {valueVariable};"
                    });
                }
                else
                {
                    switch (reference.Refered)
                    {
                        // Match the different possible refered things into proper conditions
                        case Parsing.Token token:
                            var localVar = toUnique("l");
                            methodDefinition.Add(String.Concat("auto ", localVar, " = ", token.GetMethodName(), "().value();"));

                            methodDefinition.Add($"for (;{localVar} != 0; {localVar}--)");
                            methodDefinition.Add(new ScopePart
                            {
                                "next();"
                            });
                            break;
                       case Parsing.Production production:
                            methodDefinition.Add(String.Concat(production.ToCppMatchMethodName(cppOptions), "();"));
                            break;
                       case Parsing.LeftRecursive leftRecursive:
                            methodDefinition.Add(String.Concat(leftRecursive.ToCppMatchMethodName(cppOptions), "();"));
                            break;
                       default: throw new FatalException();
                    }
                }
                methodDefinition.Add($@"skip();");
            }

            // Handle any following statement too
            foreach (var it in match.Statements)
            {
                switch (it)
                {
                    case Parsing.Statements.Set set:
                        methodDefinition.AddRange(set.ToParts(cppOptions));
                        break;
                    default: throw new NotImplementedException();
                }
            }
            methodDefinition.Add("return true;");
            return methodDefinition;
        }
        /// <summary>
        /// Receives the <see cref="ICppPart"/> for the provided <paramref name="alternatives"/>.
        /// If <paramref name="isCanMethod"/> is true, the alternatives will only check wether it can be matched,
        /// not generating any code to actually alternatives.
        /// </summary>
        /// <remarks>
        /// Alternatives Methods always are of the following prototype:
        /// <code>bool function(bool is_can, type actual)</code>
        /// where <code>function</code> is the name of the alternatives function and <code>type</code> is the calling structure type.
        /// </remarks>
        /// <param name="alternatives"></param>
        /// <param name="cppOptions"></param>
        /// <param name="typeName">The type the <paramref name="alternatives"/> gets to capture things onto.</param>
        /// <returns></returns>
        public static MethodDefinition CreateMethodDefinition(this Parsing.Statements.Alternatives alternatives, CppOptions cppOptions, string typeName)
        {
            int ___localsCount = 0;
            string toUnique(string str) => String.Concat(str, (++___localsCount).ToString());
            var methodDefinition = new MethodDefinition(
                EType.Boolean,
                cppOptions.ToUnique(String.Concat(cppOptions.MethodsPrefix, "alternatives")),
                new ArgImpl { Name = isCanVariable, Type = EType.Boolean },
                new ArgImpl { Name = classInstanceVariable, TypeString = typeName }
            );
            // Unique Variables
            string? resetable = toUnique("resetable");



            var matches = alternatives.Matches.ToArray();


            methodDefinition.Add(new FullBody
            {
                $@"resetable {resetable}(*this);",
            });
            bool isFirst = true;
            foreach (var match in matches)
            {
                methodDefinition.Add(new IfPart(isFirst, $@"{cppOptions.FromCache(match).Name}(true, {{}})")
                {
                    new IfPart(IfPart.EIfScope.If, isCanVariable)
                    {
                        $@"return true;"
                    },
                    new IfPart(IfPart.EIfScope.Else, null)
                    {
                        $@"{resetable}.reset();",
                        $@"{cppOptions.FromCache(match).Name}(false, {classInstanceVariable});",
                        $@"return true;"
                    }
                });
                isFirst = false;
            }
            methodDefinition.Add($@"{resetable}.reset();");
            methodDefinition.Add($@"return false;");
            return methodDefinition;
        }
        public static IEnumerable<ICppPart> ToParts(this Parsing.Statements.Set set, CppOptions cppOptions)
        {
            yield return new FullBody { $"if (!{isCanVariable})" };
            var scope = new ScopePart();
            switch (set.ActiveScope)
            {
                case Parsing.EActiveScope.capture:
                    {
                        var first = set.Statements.First();
                        switch (first)
                        {
                            case Parsing.Expressions.Bool @bool:
                                scope.Add(new FullBody { $"{classInstanceVariable}->{set.Property} = {@bool.Value};" });
                                break;
                            case Parsing.Expressions.CreateNewBoolean:
                                scope.Add(new FullBody { $"{classInstanceVariable}->{set.Property} = false;" });
                                break;
                            case Parsing.Expressions.Character @char:
                                scope.Add(new FullBody { $"{classInstanceVariable}->{set.Property} = '{@char.Value}';" });
                                break;
                            case Parsing.Expressions.CreateNewCharacter:
                                scope.Add(new FullBody { $"{classInstanceVariable}->{set.Property} = '\0';" });
                                break;
                            case Parsing.Expressions.Number number:
                                scope.Add(new FullBody { $"{classInstanceVariable}->{set.Property} = {number.Value};" });
                                break;
                            case Parsing.Expressions.CreateNewNumber:
                                scope.Add(new FullBody { $"{classInstanceVariable}->{set.Property} = 0;" });
                                break;
                            default:
                                throw new FatalException();
                        }
                    }
                    break;
                case Parsing.EActiveScope.global:
                case Parsing.EActiveScope.auto:
                case Parsing.EActiveScope.local:
                default:
                    throw new NotImplementedException();
            }
            yield return scope;
        }
    }
}
