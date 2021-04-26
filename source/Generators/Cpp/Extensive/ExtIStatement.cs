using System;
using System.Collections.Generic;
using System.Linq;

namespace XCG.Generators.Cpp.Extensive
{
    internal static class ExtIStatement
    {
        public static IEnumerable<ICppPart> PrepareStatementMethods(this Parsing.IStatement statement, string cppTypeName, string cppStateTypeName, CppOptions cppOptions)
        {
            IEnumerable<ICppPart> switcharoo(object obj)
            {
                switch (obj)
                {
                    case Parsing.Statements.Alternatives alternatives:
                        foreach (var yielded in PrepareStatementMethods(alternatives, cppTypeName, cppStateTypeName, cppOptions))
                        {
                            yield return yielded;
                        }
                        yield return cppOptions.FromCacheOrCreate(obj, (m) => alternatives.CreateMethodDefinition(cppOptions, cppTypeName.ToCppSharedPtrType(), cppStateTypeName));
                        break;
                    case Parsing.Statements.Match match:
                        foreach (var yielded in PrepareStatementMethods(match, cppTypeName, cppStateTypeName, cppOptions))
                        {
                            yield return yielded;
                        }
                        yield return cppOptions.FromCacheOrCreate(obj, (m) => match.CreateMethodDefinition(cppOptions, 0, cppTypeName.ToCppSharedPtrType(), cppStateTypeName));
                        break;
                    case Parsing.Statements.While @while:
                        foreach (var yielded in PrepareStatementMethods(@while, cppTypeName, cppStateTypeName, cppOptions).Concat(switcharoo(@while.Condition!)))
                        {
                            yield return yielded;
                        }
                        yield return cppOptions.FromCacheOrCreate(obj, (m) => @while.CreateMethodDefinition(cppOptions, cppTypeName.ToCppSharedPtrType(), cppStateTypeName));
                        break;
                    case Parsing.Statements.If @if:
                        foreach (var yielded in PrepareStatementMethods(@if, cppTypeName, cppStateTypeName, cppOptions).Concat(switcharoo(@if.Condition!)))
                        {
                            yield return yielded;
                        }
                        yield return cppOptions.FromCacheOrCreate(obj, (m) => @if.CreateMethodDefinition(cppOptions, cppTypeName.ToCppSharedPtrType(), cppStateTypeName));
                        break;
                    case Parsing.Statements.Print print:
                    case Parsing.Statements.Set set:
                    case Parsing.Statements.Get get:
                    case Parsing.EOF:
                        break;
                    default:
                        throw new NotImplementedException();
                }
            }
            // Output matches
            foreach (var it in statement.Statements)
            {
                foreach (var yielded in switcharoo(it))
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
                .SelectMany((q) => q.Item1.Parts.Where((q) => q is Parsing.Reference).Cast<Parsing.Reference>().Select((part) => (Reference: part, Parents: q.Item2)))
                .Where((q) => q.Reference.IsCaptured)
                .ToArray();
            var captureDefinitions = new Dictionary<string, CaptureDefinition>();
            foreach ((var captureModifyingSet, var parents) in captureModifyingSetTuples)
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
                if (parents.Any((q) => q is Parsing.Statements.While))
                {
                    captureDefinition.IsSingleHit = false;
                }
                cppOptions.CaptureDefinitionsMap.Add(captureModifyingSet, captureDefinition);
            }
            foreach ((var captureContainingReference, var parents)  in captureContainingReferenceTuples)
            {
                TypeImpl typeImpl = captureContainingReference.Refered switch
                {
                    Parsing.Token token => new TypeImpl { Type = EType.Token },
                    Parsing.Production production => new TypeImpl { TypeString = production.ToCppTypeName(cppOptions, false).ToCppSharedPtrType() },
                    Parsing.LeftRecursive leftRecursion => new TypeImpl { TypeString = leftRecursion.ToCppTypeName(cppOptions, false).ToCppSharedPtrType() },
                    _ => throw new FatalException()
                };
                string? captureName = captureContainingReference.CaptureName?.ToCppName() ?? throw new FatalException();
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
                cppOptions.CaptureDefinitionsMap.Add(captureContainingReference, captureDefinition);
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
        public static ClassDefinition GetStateDefinition(this Parsing.IStatement statement, CppOptions cppOptions)
        {
            var captureModifyingSets = statement.FindChildren<Parsing.Statements.Set>()
                .Where((q) => q.ActiveScope == Parsing.EActiveScope.local)
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
                var typeImpl = captureModifyingSet.ToTypeImpl(cppOptions);
                if (!captureDefinition.Types.Contains(typeImpl))
                {
                    captureDefinition.Types.Add(typeImpl);
                }
            }

            return new ClassDefinition(statement switch
            {
                Parsing.Production production => production.ToCppStateTypeName(cppOptions, false),
                Parsing.LeftRecursive leftRecursion => leftRecursion.ToCppStateTypeName(cppOptions, false),
                _ => throw new FatalException()
            })
            {
                PublicParts = new List<ICppPart>(captureDefinitions.Values)
            };
        }
        public static IEnumerable<ICppPart> GetEvaluationResult(this Parsing.IStatement statement, CppOptions cppOptions, string variable, bool createVariable)
        {
            switch (statement)
            {
                default:
                    throw new NotImplementedException();
                case Parsing.Statements.Match match:
                    if (createVariable)
                    {
                        yield return new VariableDefinition(EType.Boolean, variable, $@"{cppOptions.FromCache(match).Name}(true, {Constants.classInstanceVariable}, {Constants.stateInstanceVariable})");
                    }
                    else
                    {
                        yield return new FullBody { $@"{variable} = {cppOptions.FromCache(match).Name}(true, {Constants.classInstanceVariable}, {Constants.stateInstanceVariable});" };
                    }
                    break;
                case Parsing.EOF:
                    if (createVariable)
                    {
                        yield return new VariableDefinition(EType.Boolean, variable, $@"current() == '\0'");
                    }
                    else
                    {
                        yield return new FullBody { $@"{variable} = current() == '\0';" };
                    }
                    break;
                case Parsing.Statements.Get get:
                    throw new NotImplementedException();
            }
        }
        public static IEnumerable<ICppPart> Handle(this IEnumerable<Parsing.IStatement> statements, CppOptions cppOptions, bool isCan, Func<string, string> toUnique)
        {

            foreach (var it in statements)
            {
                switch (it)
                {
                    case Parsing.Statements.Match match:
                        yield return new IfPart(IfPart.EIfScope.If, $"{cppOptions.FromCache(match).Name}({isCan.ToString().ToLower()}, {Constants.classInstanceVariable}, {Constants.stateInstanceVariable})")
                        {
                            $@"skip();",
                        };
                        yield return new IfPart(IfPart.EIfScope.Else, Constants.isCanVariable)
                        {
                            new ReturnPart(EValueConstant.False),
                        };
                        yield return new IfPart(IfPart.EIfScope.Else, null)
                        {
                            $@"report(""Failed to match {{ {String.Join(", ", match.Parts.Select((q) => q.ToString()))} }}"");",
                            new ReturnPart(EValueConstant.False),
                        };
                        break;
                    case Parsing.Statements.Alternatives alternatives:
                        if (alternatives.CatchesErrors)
                        {
                            if (isCan)
                            {
                                yield return new WhilePart($@"!{cppOptions.FromCache(alternatives).Name}(true, {Constants.classInstanceVariable}, {Constants.stateInstanceVariable}) && current() != '\0'")
                                {
                                    "next();"
                                };
                            }
                            else
                            {
                                var resetable = toUnique("resetable");
                                yield return new IfPart(IfPart.EIfScope.If, $@"!{cppOptions.FromCache(alternatives).Name}(false, {Constants.classInstanceVariable}, {Constants.stateInstanceVariable})")
                                {
                                    new WhilePart($@"current() != '\0'")
                                    {
                                        $@"resetable {resetable}(*this);",
                                        new IfPart(IfPart.EIfScope.If, $@"{cppOptions.FromCache(alternatives).Name}(true, {Constants.classInstanceVariable}, {Constants.stateInstanceVariable})")
                                        {
                                            $@"{resetable}.reset();",
                                            $@"break;",
                                        },
                                        "next();"
                                    },
                                };
                            }
                        }
                        else
                        {
                            yield return new FullBody { $"{cppOptions.FromCache(alternatives).Name}({isCan.ToString().ToLower()}, {Constants.classInstanceVariable}, {Constants.stateInstanceVariable});" };
                        }
                        break;
                    case Parsing.Statements.If @if:
                        yield return new FullBody { $"{cppOptions.FromCache(@if).Name}({isCan.ToString().ToLower()}, {Constants.classInstanceVariable}, {Constants.stateInstanceVariable});" };
                        break;
                    case Parsing.Statements.While @while2:
                        yield return new FullBody { $"{cppOptions.FromCache(@while2).Name}({isCan.ToString().ToLower()}, {Constants.classInstanceVariable}, {Constants.stateInstanceVariable});" };
                        break;
                    case Parsing.Statements.Set set:
                        foreach (var part in set.ToParts(cppOptions))
                        {
                            yield return part;
                        }
                        break;
                    default: throw new NotImplementedException();
                }
            }
        }
    }
}
