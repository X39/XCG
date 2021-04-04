using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Generators.Cpp
{
    internal static class Extensions
    {
        public static string GetMethodName(this Parsing.Token token)
        {
            return String.Concat("token_", token.Identifier.Replace('-', '_').Replace('@', '_').ToLower());
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
            var methodDefinition = new MethodDefinition(EType.OptionalSizeT, token.GetMethodName());
            methodDefinition.Add(new FullBody { $@"auto r = resetable(*this);" });

            foreach (var statement in token.Statements)
            {
                if (statement is Parsing.TokenStatements.Require require)
                {
                    var scopePart = new ScopePart { new VariableDefinition(EType.SizeT, "count", "0") };
                    methodDefinition.Add(scopePart);
                    var localLoop = require.Range.To > 1 && require.Range.To != Int32.MaxValue ? new WhileLoopPart($"current() != '\\0' && count < {require.Range.To}") : new WhileLoopPart("current() != '\\0'");
                    scopePart.Add(localLoop);
                    int localsCount = 0;
                    bool isFirst = true;
                    foreach (var part in require.Parts)
                    {
                        if (part is Parsing.Word word)
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
    }
}
