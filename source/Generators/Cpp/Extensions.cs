using System;
using System.Collections.Generic;
using System.Linq;

namespace XCG.Generators.Cpp
{
    internal static class Extensions
    {
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
            return String.Concat("p_", production.Identifier.ToCppName());
        }

        public static string ToCppTypeName(this Parsing.LeftRecursive leftRecursive, CppOptions cppOptions)
        {
            return String.Concat("lr_", leftRecursive.Identifier.ToCppName());
        }

        public static string GetTestMethodName(this Parsing.Production production)
        {
            return String.Concat("prod_test_", production.Identifier.Replace('-', '_').ToLower());
        }
        public static string GetYieldMethodName(this Parsing.Production production)
        {
            return String.Concat("prod_yield_", production.Identifier.Replace('-', '_').ToLower());
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
                var captureName = captureContainingReference.CaptureName ?? $"capture{captureDefinitions.Count + 1}";
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
            // ToDo: Implement production
            yield break;
        }
    }
}
