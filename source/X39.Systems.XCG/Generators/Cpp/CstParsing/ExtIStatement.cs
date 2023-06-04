using System;
using System.Collections.Generic;
using System.Linq;
using X39.Systems.XCG.Generators.Cpp.CodeGeneration;

namespace X39.Systems.XCG.Generators.Cpp.CstParsing;

internal static class ExtIStatement
{
    public static IEnumerable<ICppPart> PrepareStatementMethods(this Parsing.IStatement statement,
        string cppTypeName, string cppStateTypeName, CppOptions cppOptions)
    {
        // ReSharper disable once IdentifierTypo
        IEnumerable<ICppPart> Switcharoo(object obj)
        {
            switch (obj)
            {
                case Parsing.Statements.Alternatives alternatives:
                    foreach (var yielded in PrepareStatementMethods(alternatives, cppTypeName, cppStateTypeName,
                                 cppOptions))
                    {
                        yield return yielded;
                    }

                    yield return cppOptions.FromCacheOrCreate(obj,
                        (_) => alternatives.CreateMethodDefinition(cppOptions, cppTypeName.ToCppSharedPtrType(),
                            cppStateTypeName));
                    break;
                case Parsing.Statements.Match match:
                    foreach (var yielded in PrepareStatementMethods(match, cppTypeName, cppStateTypeName,
                                 cppOptions))
                    {
                        yield return yielded;
                    }

                    yield return cppOptions.FromCacheOrCreate(obj,
                        (_) => match.CreateMethodDefinition(cppOptions, 0, cppTypeName.ToCppSharedPtrType(),
                            cppStateTypeName));
                    break;
                case Parsing.Statements.While @while:
                    foreach (var yielded in PrepareStatementMethods(@while, cppTypeName, cppStateTypeName,
                                 cppOptions).Concat(Switcharoo(@while.Condition!)))
                    {
                        yield return yielded;
                    }

                    yield return cppOptions.FromCacheOrCreate(obj,
                        (_) => @while.CreateMethodDefinition(cppOptions, cppTypeName.ToCppSharedPtrType(),
                            cppStateTypeName));
                    break;
                case Parsing.Statements.If @if:
                    foreach (var yielded in PrepareStatementMethods(@if, cppTypeName, cppStateTypeName, cppOptions)
                                 .Concat(Switcharoo(@if.Condition!)))
                    {
                        yield return yielded;
                    }

                    yield return cppOptions.FromCacheOrCreate(obj,
                        (_) => @if.CreateMethodDefinition(cppOptions, cppTypeName.ToCppSharedPtrType(),
                            cppStateTypeName));
                    break;
                case Parsing.Statements.Print:
                case Parsing.Statements.Set:
                case Parsing.Statements.Get:
                case Parsing.EndOfFile:
                case Parsing.EndOfLine:
                case Parsing.Reference:
                    break;
                default:
                    throw new NotImplementedException();
            }
        }

        // Output matches
        foreach (var it in statement.Statements)
        {
            foreach (var yielded in Switcharoo(it))
            {
                yield return yielded;
            }
        }
    }

    public static ClassDefinition GetClassDefinition(this Parsing.IStatement statement, CppOptions cppOptions)
    {
        var captureModifyingSetTuples = statement.FindChildrenWithParents<Parsing.Statements.Set>()
            .Where((q) => q.Item1.ActiveScope == Parsing.EActiveScope.capture)
            .ToArray();
        var captureContainingReferenceTuples = statement.FindChildrenWithParents<Parsing.Statements.Match>()
            .SelectMany((q) =>
                q.Item1.Matches.Where((matchPart) => matchPart is Parsing.Reference).Cast<Parsing.Reference>()
                    .Select((part) => (Reference: part, Parents: q.Item2)))
            .Where((q) => q.Reference.IsCaptured)
            .ToArray();
        var captureDefinitions = new Dictionary<string, CaptureDefinition>();
        foreach (var (captureModifyingSet, parents) in captureModifyingSetTuples)
        {
            var captureName = captureModifyingSet.Property.ToCppName();
            if (!captureDefinitions.TryGetValue(captureName, out var captureDefinition))
            {
                captureDefinition = new CaptureDefinition(captureName);
                captureDefinitions[captureName] = captureDefinition;
            }

            var typeImpl = new TypeImpl
            {
                Type = captureModifyingSet.Children.First() switch
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

            if (parents.Any((q) => q is Parsing.Statements.While))
            {
                captureDefinition.IsSingleHit = false;
            }

            cppOptions.ClassCaptureDefinitionsMap.Add(captureModifyingSet, captureDefinition);
        }

        foreach (var (captureContainingReference, parents) in captureContainingReferenceTuples)
        {
            var typeImpl = captureContainingReference.Referred switch
            {
                Parsing.Token => new TypeImpl {Type = EType.Token},
                Parsing.Production production => new TypeImpl
                    {TypeString = production.ToCppTypeName(cppOptions, false).ToCppSharedPtrType()},
                Parsing.LeftRecursive leftRecursion => new TypeImpl
                    {TypeString = leftRecursion.ToCppTypeName(cppOptions, false).ToCppSharedPtrType()},
                _ => throw new FatalException()
            };
            var captureName = captureContainingReference.CaptureName?.ToCppName() ?? throw new FatalException();
            if (!captureDefinitions.TryGetValue(captureName, out var captureDefinition))
            {
                captureDefinition = new CaptureDefinition(captureName);
                captureDefinitions[captureName] = captureDefinition;
            }

            if (!captureDefinition.Types.Contains(typeImpl))
            {
                captureDefinition.Types.Add(typeImpl);
            }

            if (parents.Any((q) => q is Parsing.Statements.While))
            {
                captureDefinition.IsSingleHit = false;
            }

            cppOptions.ClassCaptureDefinitionsMap.Add(captureContainingReference, captureDefinition);
        }


        // ToDo: Implement optional captures with multiple types (std::variant default-initializes to first variant, we want std::optional here instead)

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

    public static ClassDefinition GetStateDefinition(this Parsing.IStatement statement, CppOptions cppOptions)
    {
        var captureModifyingSets = statement.FindChildren<Parsing.Statements.Set>()
            .Where((q) => q.ActiveScope == Parsing.EActiveScope.local)
            .ToArray();
        var captureDefinitions = new Dictionary<string, CaptureDefinition>();
        var stateClassName = statement switch
        {
            Parsing.Production production => production.ToCppStateTypeName(cppOptions, false),
            Parsing.LeftRecursive leftRecursion => leftRecursion.ToCppStateTypeName(cppOptions, false),
            _ => throw new FatalException()
        };
        foreach (var captureModifyingSet in captureModifyingSets)
        {
            var captureName = captureModifyingSet.Property.ToCppName();
            if (!captureDefinitions.TryGetValue(captureName, out var captureDefinition))
            {
                captureDefinition = new CaptureDefinition(captureName);
                captureDefinitions[captureName] = captureDefinition;
            }

            var typeImpl = captureModifyingSet.ToTypeImpl(cppOptions);
            if (!captureDefinition.Types.Contains(typeImpl))
            {
                captureDefinition.Types.Add(typeImpl);
            }

            if (!cppOptions.StateCaptureDefinitionsMap.ContainsKey((stateClassName, captureModifyingSet.Property)))
            {
                cppOptions.StateCaptureDefinitionsMap.Add((stateClassName, captureModifyingSet.Property),
                    captureDefinition);
            }
        }

        return new ClassDefinition(stateClassName)
        {
            PublicParts = new List<ICppPart>(captureDefinitions.Values)
        };
    }

    public static IEnumerable<ICppPart> GetEvaluationResult(this Parsing.IStatement statement,
        CppOptions cppOptions, string stateTypeName, string variable, bool createVariable,
        Func<string, string> toUnique)
    {
        switch (statement)
        {
            default:
                throw new NotImplementedException();
            case Parsing.Token token:
                if (createVariable)
                {
                    var lengthVariable = toUnique("l");
                    var indexVariable = toUnique("i");
                    yield return new VariableDefinition(EType.Boolean, variable, "false");
                    yield return new FullBody {$@"auto {lengthVariable} = {token.GetMethodName()}(0);"};
                    yield return new IfPart(IfPart.EIfScope.If, $@"{lengthVariable}.has_value()")
                    {
                        $@"for (auto {indexVariable} = {lengthVariable}.value(); {indexVariable} != 0; {indexVariable}--)",
                        new ScopePart
                        {
                            "next();"
                        },
                        $@"skip();",
                        $@"{variable} = true;",
                    };
                }
                else
                {
                    var lengthVariable = toUnique("l");
                    var indexVariable = toUnique("i");
                    yield return new FullBody {$@"auto {lengthVariable} = {token.GetMethodName()}(0);"};
                    yield return new IfPart(IfPart.EIfScope.If, $@"{lengthVariable}.has_value()")
                    {
                        $@"for (auto {indexVariable} = {lengthVariable}.value(); {indexVariable} != 0; {indexVariable}--)",
                        new ScopePart
                        {
                            "next();"
                        },
                        $@"skip();",
                        $@"{variable} = true;",
                    };
                    yield return new IfPart(IfPart.EIfScope.Else, null)
                    {
                        $@"{variable} = false;",
                    };
                }

                break;
            case Parsing.Statements.Match match:
                if (createVariable)
                {
                    yield return new VariableDefinition(EType.Boolean, variable,
                        $@"{cppOptions.FromCache(match).Name}(true, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)");
                }
                else
                {
                    yield return new FullBody
                    {
                        $@"{variable} = {cppOptions.FromCache(match).Name}(true, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1);"
                    };
                }

                break;
            case Parsing.EndOfFile:
                if (createVariable)
                {
                    yield return new VariableDefinition(EType.Boolean, variable, $@"current() == '\0'");
                }
                else
                {
                    yield return new FullBody {$@"{variable} = current() == '\0';"};
                }

                break;
            case Parsing.EndOfLine:
                if (createVariable)
                {
                    yield return new VariableDefinition(EType.Boolean, variable, $@"current() == '\n'");
                }
                else
                {
                    yield return new FullBody {$@"{variable} = current() == '\n';"};
                }

                break;
            case Parsing.Statements.Get get:
                if (createVariable)
                {
                    yield return new VariableDefinition(EType.Boolean, variable,
                        get.GetEvaluatedValue(cppOptions, stateTypeName));
                }
                else
                {
                    yield return new FullBody
                        {$@"{variable} = {get.GetEvaluatedValue(cppOptions, stateTypeName)};"};
                }

                break;
        }
    }

    public static IEnumerable<ICppPart> Handle(this IEnumerable<Parsing.IStatement> statements,
        CppOptions cppOptions, bool isCan, Func<string, string> toUnique)
    {
        foreach (var it in statements)
        {
            switch (it)
            {
                case Parsing.Statements.Match match:
                    yield return new IfPart(IfPart.EIfScope.If,
                        $"{cppOptions.FromCache(match).Name}({isCan.ToString().ToLower()}, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
                    {
                        $@"skip();",
                    };
                    yield return new IfPart(IfPart.EIfScope.Else, Constants.IsCanVariable)
                    {
                        new DebugPart {$@"trace(""Returning false on {match}"", {Constants.DepthVariable});"},
                        new ReturnPart(EValueConstant.False),
                    };
                    yield return new IfPart(IfPart.EIfScope.Else, null)
                    {
                        $@"report(""Failed to match {{ {string.Join(", ", match.Matches.Select((q) => q.ToString()))} }}"", {Constants.DepthVariable});",
                        new DebugPart {$@"trace(""Returning false on {match}"", {Constants.DepthVariable});"},
                        new ReturnPart(EValueConstant.False),
                    };
                    break;
                case Parsing.Statements.Alternatives alternatives:
                    if (alternatives.CatchesErrors)
                    {
                        if (isCan)
                        {
                            yield return new WhilePart(
                                $@"!{cppOptions.FromCache(alternatives).Name}(true, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1) && current() != '\0'")
                            {
                                "next();"
                            };
                        }
                        else
                        {
                            var resettable = toUnique("resettable");
                            yield return new IfPart(IfPart.EIfScope.If,
                                $@"!{cppOptions.FromCache(alternatives).Name}(false, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
                            {
                                new WhilePart($@"current() != '\0'")
                                {
                                    $@"resettable {resettable}(*this);",
                                    new IfPart(IfPart.EIfScope.If,
                                        $@"{cppOptions.FromCache(alternatives).Name}(true, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
                                    {
                                        $@"{resettable}.reset();",
                                        $@"break;",
                                    },
                                    "next();"
                                },
                            };
                        }
                    }
                    else
                    {
                        yield return new FullBody
                        {
                            $"{cppOptions.FromCache(alternatives).Name}({isCan.ToString().ToLower()}, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1);"
                        };
                    }

                    break;
                case Parsing.Statements.If @if:
                    yield return new FullBody
                    {
                        $"{cppOptions.FromCache(@if).Name}({isCan.ToString().ToLower()}, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1);"
                    };
                    break;
                case Parsing.Statements.While @while2:
                    yield return new FullBody
                    {
                        $"{cppOptions.FromCache(@while2).Name}({isCan.ToString().ToLower()}, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1);"
                    };
                    break;
                case Parsing.Statements.Set set:
                    foreach (var part in set.ToParts(cppOptions))
                    {
                        yield return part;
                    }

                    break;
                case Parsing.Statements.Print print:
                    foreach (var part in print.ToParts(cppOptions))
                    {
                        yield return part;
                    }

                    break;
                default: throw new NotImplementedException();
            }
        }
    }
}