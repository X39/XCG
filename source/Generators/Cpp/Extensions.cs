using System;
using System.Collections.Generic;
using System.Linq;

namespace XCG.Generators.Cpp
{
    internal static class Extensions
    {
        private const string isCanVariable = "isCan";
        private const string classInstanceVariable = "actual";
        public static string ToCppSharedPtr(this string str)
        {
            return String.Concat("std::shared_ptr<", str, ">");
        }
        public static string ToCppName(this string str)
        {
            return String.Concat(str.Replace('-', '_').Replace('@', '_').ToLower());
        }
        public static string GetMethodName(this Parsing.Token token)
        {
            return String.Concat("token_", token.Identifier.Replace('-', '_').Replace('@', '_').ToLower());
        }
        public static string ToCppTypeName(this Parsing.Token token, CppOptions cppOptions)
        {
            return "token";
        }

        public static string ToCppTypeName(this Parsing.Production production, CppOptions cppOptions)
        {
            return String.Concat(cppOptions.TypePrefix, "p_", production.Identifier.ToCppName());
        }
        public static string ToCppCanMatchMethodName(this Parsing.Production production, CppOptions cppOptions)
        {
            return String.Concat(cppOptions.MethodsPrefix, "p_can_", production.Identifier.ToCppName());
        }
        public static string ToCppMatchMethodName(this Parsing.Production production, CppOptions cppOptions)
        {
            return String.Concat(cppOptions.MethodsPrefix, "p_match_", production.Identifier.ToCppName());
        }

        public static string ToCppTypeName(this Parsing.LeftRecursive leftRecursive, CppOptions cppOptions)
        {
            return String.Concat(cppOptions.TypePrefix, "lr_", leftRecursive.Identifier.ToCppName());
        }
        public static string ToCppCanMatchMethodName(this Parsing.LeftRecursive leftRecursive, CppOptions cppOptions)
        {
            return String.Concat(cppOptions.MethodsPrefix, "lr_can_", leftRecursive.Identifier.ToCppName());
        }
        public static string ToCppMatchMethodName(this Parsing.LeftRecursive leftRecursive, CppOptions cppOptions)
        {
            return String.Concat(cppOptions.MethodsPrefix, "lr_match_", leftRecursive.Identifier.ToCppName());
        }


        public static IEnumerable<ICppPart> ToParts(this Parsing.Token token)
        {
            var methodDefinition = new MethodDefinition(EType.OptionalSizeT, token.GetMethodName())
            {
                new FullBody { $@"auto r = resetable(*this);" }
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
                            localLoop.Add(new FullBody
                            {
                                $@"{(isFirst ? String.Empty : "else ")}if ('{range.Start}' <= current() && current() <= '{range.End}')",
                                $@"{{",
                                $@"    count++;",
                                $@"    next();",
                                $@"    continue;",
                                $@"}}",
                            });
                        }
                        else if (part is Parsing.Reference reference)
                        {
                            if (reference.Refered is Parsing.Token referedToken)
                            {
                                localLoop.Add(new FullBody
                                {
                                    $@"auto l{++localsCount} = {referedToken.GetMethodName()}();",
                                    $@"if (l{localsCount}.has_value())",
                                    $@"{{",
                                    $@"    count++;",
                                    $@"    for (size_t i = 0; i < l{localsCount}; i++)",
                                    $@"    {{",
                                    $@"        next();",
                                    $@"    }}",
                                    $@"    continue;",
                                    $@"}}",
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
                    scopePart.Add(new FullBody
                    {
                        $@"if (count < {require.Range.From})",
                        $@"{{",
                        $@"    r.reset();",
                        $@"    return {{}};",
                        $@"}}",
                    });
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

            methodDefinition.Add(new FullBody { $@"return {{}};" });
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
                var captureName = captureModifyingSet.Property.ToCppName();
                if (!captureDefinitions.TryGetValue(captureName, out var captureDefinition))
                {
                    captureDefinition = new CaptureDefinition(captureName);
                    captureDefinitions[captureName] = captureDefinition;
                }
                var typeImpl = new TypeImpl
                {
                    Type = captureModifyingSet.Statements.First() switch
                    {
                        Parsing.Expressions.CreateNewBoolean => EType.Boolean,
                        Parsing.Expressions.Bool => EType.Boolean,
                        Parsing.Expressions.CreateNewCharacter => EType.Char,
                        Parsing.Expressions.Character => EType.Char,
                        Parsing.Expressions.CreateNewNumber => EType.Double,
                        Parsing.Expressions.Number => EType.Double,
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
                string typeName = captureContainingReference.Refered switch
                {
                    Parsing.Token token => token.ToCppTypeName(cppOptions),
                    Parsing.Production production => production.ToCppTypeName(cppOptions),
                    Parsing.LeftRecursive leftRecursion => leftRecursion.ToCppTypeName(cppOptions),
                    _ => throw new FatalException()
                };
                var captureName = captureContainingReference.CaptureName ?? throw new FatalException();
                if (!captureDefinitions.TryGetValue(captureName, out var captureDefinition))
                {
                    captureDefinition = new CaptureDefinition(captureName);
                    captureDefinitions[captureName] = captureDefinition;
                }
                var typeImpl = new TypeImpl { TypeString = typeName };
                if (!captureDefinition.Types.Contains(typeImpl))
                {
                    captureDefinition.Types.Add(typeImpl);
                }
            }

            return new ClassDefinition(statement switch
                {
                    Parsing.Token token => token.ToCppTypeName(cppOptions),
                    Parsing.Production production => production.ToCppTypeName(cppOptions),
                    Parsing.LeftRecursive leftRecursion => leftRecursion.ToCppTypeName(cppOptions),
                    _ => throw new FatalException()
                })
            {
                PublicParts = new List<ICppPart>(captureDefinitions.Values)
            };
        }
        public static IEnumerable<ICppPart> ToParts(this Parsing.Production production, CppOptions cppOptions)
        {
            // ToDo: Implement production
            yield break;
        }
        public static IEnumerable<ICppPart> ToParts(this Parsing.LeftRecursive leftRecursive, CppOptions cppOptions)
        {
            // ToDo: Implement leftRecursive



            // Output match for testing
            var matches = leftRecursive.Statements.Cast<Parsing.Statements.Match>().ToArray();
            var lastMatch = matches.Last();
            yield return cppOptions.FromCacheOrCreate(lastMatch, (m) => m.CreateMethodDefinition(cppOptions, 0, leftRecursive.ToCppTypeName(cppOptions).ToCppSharedPtr()));
            foreach (var it in matches.Take(matches.Length - 1))
            {
                yield return cppOptions.FromCacheOrCreate(it, (m) => m.CreateMethodDefinition(cppOptions, 1, leftRecursive.ToCppTypeName(cppOptions).ToCppSharedPtr()));
            }
        }

        /// <summary>
        /// Receives the <see cref="ICppPart"/> for the provided <paramref name="match"/>.
        /// If <paramref name="isCanMethod"/> is true, the match will only check wether it can be matched,
        /// not generating any code to actually match.
        /// </summary>
        /// <param name="match"></param>
        /// <param name="cppOptions"></param>
        /// <param name="skip">The amount of match-tokens to skip.</param>
        /// <param name="typeName">The type the <paramref name="match"/> gets to capture things onto.</param>
        /// <returns></returns>
        public static MethodDefinition CreateMethodDefinition(this Parsing.Statements.Match match, CppOptions cppOptions, int skip, string typeName)
        {
            var methodDefinition = new MethodDefinition(
                EType.Boolean,
                cppOptions.ToUnique(String.Concat(cppOptions.MethodsPrefix, "match")),
                new ArgImpl { Name = isCanVariable, Type = EType.Boolean },
                new ArgImpl { Name = classInstanceVariable, TypeString = typeName }
            );
            // Unique Variables
            var resetable = cppOptions.ToUnique("resetable");
            


            var references = match.Parts.Cast<Parsing.Reference>().Skip(skip).ToArray();


            methodDefinition.Add(new FullBody
            {
                $@"resetable {resetable}(*this);",
                $@"if ({String.Join(" && ", references.Select((reference) => reference.Refered switch{
                    // Match the different possible refered things into proper conditions
                    Parsing.Token token => String.Concat(token.GetMethodName(), "().has_value()"),
                    Parsing.Production production => String.Concat(production.ToCppCanMatchMethodName(cppOptions), "()"),
                    Parsing.LeftRecursive leftRecursive => String.Concat(leftRecursive.ToCppCanMatchMethodName(cppOptions), "()"),
                    _ => throw new FatalException()
                }))})",
            });
            var scope = new ScopePart();
            methodDefinition.Add(scope);

            // Handle actual matches
            {
                scope.Add(new FullBody { $"if (!{isCanVariable})" });
                var ifScope = new ScopePart();
                scope.Add(ifScope);
                ifScope.Add(new FullBody { $"{resetable}.reset();" });
                // capture local matches matches
                foreach (var reference in references)
                {
                    var valueVariable = cppOptions.ToUnique("val");
                    if (reference.IsCaptured)
                    {
                        var call = reference.Refered switch
                        {
                            // Match the different possible refered things into proper conditions
                            Parsing.Token token => String.Concat(token.GetMethodName(), "().value()"),
                            Parsing.Production production => String.Concat(production.ToCppMatchMethodName(cppOptions), "()"),
                            Parsing.LeftRecursive leftRecursive => String.Concat(leftRecursive.ToCppMatchMethodName(cppOptions), "()"),
                            _ => throw new FatalException()
                        };
                        ifScope.Add(new FullBody
                        {
                            $"auto {valueVariable} = {call};",
                            $"{classInstanceVariable}->{reference.CaptureName ?? throw new FatalException()} = {valueVariable};"
                        });
                    }
                    else
                    {
                        var call = reference.Refered switch
                        {
                            // Match the different possible refered things into proper conditions
                            Parsing.Token token => String.Concat(token.GetMethodName(), "()"),
                            Parsing.Production production => String.Concat(production.ToCppMatchMethodName(cppOptions), "()"),
                            Parsing.LeftRecursive leftRecursive => String.Concat(leftRecursive.ToCppMatchMethodName(cppOptions), "()"),
                            _ => throw new FatalException()
                        };
                        ifScope.Add(new FullBody
                        {
                            $"{call};"
                        });
                    }
                }
            }

            // Handle any following statement too
            foreach (var it in match.Statements)
            {
                switch (it)
                {
                    case Parsing.Statements.Set set:
                        scope.AddRange(set.ToParts(cppOptions));
                        break;
                    default: throw new NotImplementedException();
                }
            }

            methodDefinition.Add(new FullBody
            {
                $@"else",
                $@"{{",
                $@"    if ({isCanVariable})",
                $@"    {{",
                $@"        {resetable}.reset();",
                $@"    }}",
                $@"    else",
                $@"    {{",
                $@"        report(""Something moved wrong (todo: improve error messages)"");",
                $@"    }}",
                $@"}}",
            });
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
