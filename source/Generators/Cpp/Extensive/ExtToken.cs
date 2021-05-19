using System;
using System.Collections.Generic;
using System.Linq;

namespace XCG.Generators.Cpp.Extensive
{
    internal static class ExtToken
    {
        public static string GetMethodName(this Parsing.Token token)
        {
            return String.Concat("token_", token.Identifier.ToCppName().ToLower());
        }
        public static string GetCppEnumName(this Parsing.Token token)
        {
            return String.Concat(token.Identifier.ToCppName().ToUpper());
        }
        public static string ToCppTypeName(this Parsing.Token token, CppOptions cppOptions, bool full)
        {
            return String.Concat(full ? cppOptions.RootClassName : String.Empty, cppOptions.TypePrefix, cppOptions.TokenName);
        }
        public static IEnumerable<ICppPart> ToParts(this Parsing.Token token, CppOptions cppOptions)
        {
            int ___localsCount = 0;
            string toUnique(string str) => String.Concat(str, (++___localsCount).ToString());
            string? resetable = toUnique("resetable");
            var methodDefinition = new MethodDefinition(EType.OptionalSizeT, token.GetMethodName(),
                new ArgImpl { Name = Constants.depthVariable, Type = EType.SizeT })
            {
                new FullBody { $@"resetable {resetable}(*this);" }
            };

            foreach (var statement in token.Children)
            {
                if (statement is Parsing.TokenStatements.Require require)
                {
                    string countVariable = toUnique("count");
                    methodDefinition.Add(new VariableDefinition(EType.SizeT, countVariable, "0"));
                    var localLoop = require.Range.To != Int32.MaxValue ? new WhilePart($"current() != '\\0' && {countVariable} < {require.Range.To}") : new WhilePart("current() != '\\0'");
                    methodDefinition.Add(localLoop);
                    bool isFirst = true;
                    foreach (var part in require.Parts)
                    {
                        if (part is Parsing.Word word)
                        {
                            if (word.Text.Length > 1)
                            {
                                var wordHolderVariable = toUnique("str");
                                localLoop.Add(new VariableDefinition(new TypeImpl { Type = EType.Char, PointerCount = 1, IsConst = true }, wordHolderVariable, $@"""{String.Concat(word.Text.Select((c) => c.Escape()))}"""));
                                localLoop.Add(new IfPart(IfPart.EIfScope.If, $@"m_contents.length() - m_offset >= {word.Text.Length} && {(require.Negated ? "!" : String.Empty)}std::equal(m_contents.begin() + m_offset, m_contents.begin() + m_offset + {word.Text.Length}, {wordHolderVariable}, {wordHolderVariable} + {word.Text.Length})")
                                {
                                    $@"{countVariable}++;",
                                    $@"for (size_t i = 0; i < {word.Text.Length}; i++)",
                                    $@"{{",
                                    $@"    next();",
                                    $@"}}",
                                    $@"continue;",
                                });
                            }
                            else
                            {
                                localLoop.Add(new IfPart(IfPart.EIfScope.If, $@"current() {(require.Negated ? "!" : "=")}= '{word.Text.First().Escape()}'")
                                {
                                    $@"{countVariable}++;",
                                    $@"next();",
                                    $@"continue;",
                                });
                            }
                        }
                        else if (part is Parsing.CharacterRange range)
                        {
                            localLoop.Add(new IfPart(isFirst, $@"{(require.Negated ? "!" : String.Empty)}('{range.Start}' <= current() && current() <= '{range.End}')")
                            {
                                $@"{countVariable}++;",
                                $@"next();",
                                $@"continue;",
                            });
                        }
                        else if (part is Parsing.Reference reference)
                        {
                            if (reference.Refered is Parsing.Token referedToken)
                            {
                                var tokenHolderVariable = toUnique("res");
                                localLoop.Add(new VariableDefinition(new TypeImpl { Type = EType.OptionalSizeT }, tokenHolderVariable, $@"{referedToken.GetMethodName()}({Constants.depthVariable} + 1)"));
                                localLoop.Add(new IfPart(IfPart.EIfScope.If, $@"{tokenHolderVariable}.has_value()")
                                {
                                    $@"{countVariable}++;",
                                    $@"for (size_t i = 0; i < {tokenHolderVariable}; i++)",
                                    $@"{{",
                                    $@"    next();",
                                    $@"}}",
                                    $@"continue;",
                                });
                            }
                            else
                            {
                                throw new FatalException("Unimplemented require part");
                            }
                        }
                        else
                        {
                            throw new FatalException("Unimplemented require part");
                        }
                        isFirst = false;
                    }
                    localLoop.Add(new FullBody { $@"break;" });
                    if (require.Range.From > 0)
                    {
                        methodDefinition.Add(new IfPart(IfPart.EIfScope.If, $@"{countVariable} < {require.Range.From}")
                        {
                            $@"{resetable}.reset();",
                            new DebugPart { $@"trace(""Returning EmptyClosure on {token.Identifier}"", {Constants.depthVariable});" },
                            new ReturnPart(EValueConstant.EmptyClosure),
                        });
                    }
                }
                else if (statement is Parsing.TokenStatements.Backtrack backtrack)
                {
                    string countVariable = toUnique("count");
                    string localOffsetVariable = toUnique("loff");
                    methodDefinition.Add(new VariableDefinition(EType.SizeT, countVariable, backtrack.Range.To.ToString()));
                    methodDefinition.Add(new VariableDefinition(EType.SizeT, localOffsetVariable, "0"));
                    var localLoop = backtrack.Range.To != Int32.MaxValue ? new WhilePart($"current() != '\\0' && {countVariable} > 0") : new WhilePart("current() != '\\0'");
                    methodDefinition.Add(localLoop);
                    int localsCount = 0;
                    bool isFirst = true;
                    foreach (var part in backtrack.Parts)
                    {
                        if (part is Parsing.Word word)
                        {
                            if (word.Text.Length > 1)
                            {
                                var wordHolderVariable = toUnique("str");
                                localLoop.Add(new VariableDefinition(new TypeImpl { Type = EType.Char, PointerCount = 1, IsConst = true }, wordHolderVariable, $@"""{word.Text.Replace("\"", "\\\"")}"""));
                                localLoop.Add(new IfPart(IfPart.EIfScope.If, $@"m_offset >= {word.Text.Length} && {(!backtrack.Negated ? "!" : String.Empty)}std::equal(m_contents.begin() + m_offset - {word.Text.Length}, m_contents.begin() + m_offset, l{localsCount}, l{localsCount} + {word.Text.Length})")
                                {
                                    $@"break;"
                                });
                            }
                            else
                            {
                                localLoop.Add(new IfPart(IfPart.EIfScope.If, $@"m_offset >= 1 && m_contents[m_offset - 1] {(!backtrack.Negated ? "!" : "=")}= '{word.Text.First()}'")
                                {
                                    $@"break;"
                                });
                            }
                        }
                        else if (part is Parsing.CharacterRange range)
                        {
                            localLoop.Add(new IfPart(isFirst, $@"'m_offset >= 1 && {(!backtrack.Negated ? "!" : String.Empty)}({range.Start}' <= m_contents[m_offset - 1] && m_contents[m_offset - 1] <= '{range.End}')")
                            {
                                $@"break;"
                            });
                        }
                        else
                        {
                            throw new FatalException("Unimplemented backtrack part");
                        }
                        isFirst = false;
                    }
                    localLoop.Add(new FullBody { $@"{countVariable}--;" });
                    methodDefinition.Add(new IfPart(IfPart.EIfScope.If, $@"{countVariable} {(backtrack.Range.From > 0 ? ">=" : "!=")} {backtrack.Range.From}")
                    {
                        $@"{resetable}.reset();",
                        new DebugPart { $@"trace(""Returning EmptyClosure on {token.Identifier}"", {Constants.depthVariable});" },
                        new ReturnPart(EValueConstant.EmptyClosure),
                    });
                }
                else
                {
                    throw new FatalException("Unimplemented TokenStatement");
                }
            }

            var resultVariable = cppOptions.ToUnique("resultVariable");
            methodDefinition.Add($@"auto {resultVariable} = m_offset - {resetable}.m_offset;");
            methodDefinition.Add($@"{resetable}.reset();");
            methodDefinition.Add(new DebugPart { $@"trace((std::string(""Returning "") + std::to_string({resultVariable}) + "" on {token.Identifier}"").c_str(), {Constants.depthVariable});" });
            methodDefinition.Add(new ReturnPart(resultVariable));
            return new[] { methodDefinition };
        }
    }
}
