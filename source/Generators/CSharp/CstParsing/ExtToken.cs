using System.Collections.Generic;
using System.Linq;
using XCG.Generators.CSharp.CodeGeneration;

namespace XCG.Generators.CSharp.CstParsing;

internal static class ExtToken
{
    public static string GetMethodName(this Parsing.Token token)
    {
        return string.Concat("token_", token.Identifier.ToCppName().ToLower());
    }
    public static string GetCSharpEnumName(this Parsing.Token token)
    {
        return token.Identifier.ToCppName().ToUpper();
    }
    public static string ToCSharpTypeName(this Parsing.Token token, CSharpOptions cSharpOptions, bool full)
    {
        return string.Concat(full ? cSharpOptions.RootClassName : string.Empty, cSharpOptions.TypePrefix, cSharpOptions.TokenName);
    }
    public static IEnumerable<ICSharpPart> ToParts(this Parsing.Token token, CSharpOptions cSharpOptions)
    {
        var localsCount = 0;
        string ToUnique(string str) => string.Concat(str, (++localsCount).ToString());
        var resettable = ToUnique("resettable");
        var methodDefinition = new MethodDefinition(EType.OptionalSizeT, token.GetMethodName(),
            new ArgImpl { Name = Constants.DepthVariable, Type = EType.SizeT })
        {
            new FullBody { $@"resettable {resettable}(*this);" }
        };

        foreach (var statement in token.Children)
        {
            switch (statement)
            {
                case Parsing.TokenStatements.Require require:
                {
                    var countVariable = ToUnique("count");
                    methodDefinition.Add(new VariableDefinition(EType.SizeT, countVariable, "0"));
                    var localLoop = require.Range.To != int.MaxValue ? new WhilePart($"current() != '\\0' && {countVariable} < {require.Range.To}") : new WhilePart("current() != '\\0'");
                    methodDefinition.Add(localLoop);
                    var isFirst = true;
                    foreach (var part in require.Parts)
                    {
                        switch (part)
                        {
                            case Parsing.Word word when word.Text.Length > 1:
                            {
                                var wordHolderVariable = ToUnique("str");
                                localLoop.Add(new VariableDefinition(new TypeImpl { Type = EType.Char }, wordHolderVariable, $@"""{string.Concat(word.Text.Select((c) => c.Escape()))}"""));
                                localLoop.Add(new IfPart(IfPart.EIfScope.If, $@"_contents.length() - _offset >= {word.Text.Length} && {(require.Negated ? "!" : string.Empty)}std::equal(_contents.begin() + _offset, _contents.begin() + _offset + {word.Text.Length}, {wordHolderVariable}, {wordHolderVariable} + {word.Text.Length})")
                                {
                                    $@"{countVariable}++;",
                                    $@"for (size_t i = 0; i < {word.Text.Length}; i++)",
                                    $@"{{",
                                    $@"    next();",
                                    $@"}}",
                                    $@"continue;",
                                });
                                break;
                            }
                            case Parsing.Word word:
                                localLoop.Add(new IfPart(IfPart.EIfScope.If, $@"current() {(require.Negated ? "!" : "=")}= '{word.Text.First().Escape()}'")
                                {
                                    $@"{countVariable}++;",
                                    $@"next();",
                                    $@"continue;",
                                });
                                break;
                            case Parsing.CharacterRange range:
                                localLoop.Add(new IfPart(isFirst, $@"{(require.Negated ? "!" : string.Empty)}('{range.Start.Escape()}' <= current() && current() <= '{range.End.Escape()}')")
                                {
                                    $@"{countVariable}++;",
                                    $@"next();",
                                    $@"continue;",
                                });
                                break;
                            case Parsing.Reference {Referred: Parsing.Token referredToken}:
                            {
                                var tokenHolderVariable = ToUnique("res");
                                localLoop.Add(new VariableDefinition(new TypeImpl { Type = EType.OptionalSizeT }, tokenHolderVariable, $@"{referredToken.GetMethodName()}({Constants.DepthVariable} + 1)"));
                                localLoop.Add(new IfPart(IfPart.EIfScope.If, $@"{tokenHolderVariable}.has_value()")
                                {
                                    $@"{countVariable}++;",
                                    $@"for (size_t i = 0; i < {tokenHolderVariable}; i++)",
                                    $@"{{",
                                    $@"    next();",
                                    $@"}}",
                                    $@"continue;",
                                });
                                break;
                            }
                            case Parsing.Reference:
                                throw new FatalException("Unimplemented require part");
                            default:
                                throw new FatalException("Unimplemented require part");
                        }

                        isFirst = false;
                    }
                    localLoop.Add(new FullBody { $@"break;" });
                    if (require.Range.From > 0)
                    {
                        methodDefinition.Add(new IfPart(IfPart.EIfScope.If, $@"{countVariable} < {require.Range.From}")
                        {
                            $@"{resettable}.reset();",
                            new DebugPart { $@"trace(""Returning EmptyClosure on {token.Identifier}"", {Constants.DepthVariable});" },
                            new ReturnPart(EValueConstant.EmptyClosure),
                        });
                    }

                    break;
                }
                case Parsing.TokenStatements.Backtrack backtrack:
                {
                    var countVariable = ToUnique("count");
                    var localOffsetVariable = ToUnique("local_offset");
                    methodDefinition.Add(new VariableDefinition(EType.SizeT, countVariable, backtrack.Range.To.ToString()));
                    methodDefinition.Add(new VariableDefinition(EType.SizeT, localOffsetVariable, "0"));
                    var localLoop = backtrack.Range.To != int.MaxValue ? new WhilePart($"current() != '\\0' && {countVariable} > 0") : new WhilePart("current() != '\\0'");
                    methodDefinition.Add(localLoop);
                    var localsCount2 = 0;
                    var isFirst = true;
                    foreach (var part in backtrack.Parts)
                    {
                        switch (part)
                        {
                            case Parsing.Word word when word.Text.Length > 1:
                            {
                                var wordHolderVariable = ToUnique("str");
                                localLoop.Add(new VariableDefinition(new TypeImpl { Type = EType.Char }, wordHolderVariable, $@"""{word.Text.Replace("\"", "\\\"")}"""));
                                localLoop.Add(new IfPart(IfPart.EIfScope.If, $@"_offset >= {word.Text.Length} && {(!backtrack.Negated ? "!" : string.Empty)}std::equal(_contents.begin() + _offset - {word.Text.Length}, _contents.begin() + _offset, l{localsCount2}, l{localsCount2} + {word.Text.Length})")
                                {
                                    $@"break;"
                                });
                                break;
                            }
                            case Parsing.Word word:
                                localLoop.Add(new IfPart(IfPart.EIfScope.If, $@"_offset >= 1 && _contents[_offset - 1] {(!backtrack.Negated ? "!" : "=")}= '{word.Text.First().Escape()}'")
                                {
                                    $@"break;"
                                });
                                break;
                            case Parsing.CharacterRange range:
                                localLoop.Add(new IfPart(isFirst, $@"'_offset >= 1 && {(!backtrack.Negated ? "!" : string.Empty)}({range.Start.Escape()}' <= _contents[_offset - 1] && _contents[_offset - 1] <= '{range.End.Escape()}')")
                                {
                                    $@"break;"
                                });
                                break;
                            default:
                                throw new FatalException("Unimplemented backtrack part");
                        }

                        isFirst = false;
                    }
                    localLoop.Add(new FullBody { $@"{countVariable}--;" });
                    methodDefinition.Add(new IfPart(IfPart.EIfScope.If, $@"{countVariable} {(backtrack.Range.From > 0 ? ">=" : "!=")} {backtrack.Range.From}")
                    {
                        $@"{resettable}.reset();",
                        new DebugPart { $@"trace(""Returning EmptyClosure on {token.Identifier}"", {Constants.DepthVariable});" },
                        new ReturnPart(EValueConstant.EmptyClosure),
                    });
                    break;
                }
                default:
                    throw new FatalException("Unimplemented TokenStatement");
            }
        }

        var resultVariable = cSharpOptions.ToUnique("resultVariable");
        methodDefinition.Add($@"auto {resultVariable} = _offset - {resettable}._offset;");
        methodDefinition.Add($@"{resettable}.reset();");
        methodDefinition.Add(new DebugPart { $@"trace((std::string(""Returning "") + std::to_string({resultVariable}) + "" on {token.Identifier}"").c_str(), {Constants.DepthVariable});" });
        methodDefinition.Add(new ReturnPart(resultVariable));
        return new[] { methodDefinition };
    }
}