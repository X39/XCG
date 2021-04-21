using System;
using System.Collections.Generic;
using System.Linq;

namespace XCG.Generators.Cpp.Extensive
{
    internal static class ExtSet
    {
        public static TypeImpl ToTypeImpl(this Parsing.Statements.Set set, CppOptions cppOptions)
        {
            return new TypeImpl
            {
                Type = set.Statements.First() switch
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
        }
        public static IEnumerable<ICppPart> ToParts(this Parsing.Statements.Set set, CppOptions cppOptions)
        {
            yield return new FullBody { $"if (!{Constants.isCanVariable})" };
            var scope = new ScopePart();
            switch (set.ActiveScope)
            {
                case Parsing.EActiveScope.capture:
                    {
                        var first = set.Statements.First();
                        switch (first)
                        {
                            case Parsing.Expressions.Bool @bool:
                                scope.Add(new FullBody { $"{Constants.classInstanceVariable}->{set.Property} = {@bool.Value};" });
                                break;
                            case Parsing.Expressions.CreateNewBoolean:
                                scope.Add(new FullBody { $"{Constants.classInstanceVariable}->{set.Property} = false;" });
                                break;
                            case Parsing.Expressions.Character @char:
                                scope.Add(new FullBody { $"{Constants.classInstanceVariable}->{set.Property} = '{@char.Value}';" });
                                break;
                            case Parsing.Expressions.CreateNewCharacter:
                                scope.Add(new FullBody { $"{Constants.classInstanceVariable}->{set.Property} = '\0';" });
                                break;
                            case Parsing.Expressions.Number number:
                                scope.Add(new FullBody { $"{Constants.classInstanceVariable}->{set.Property} = {number.Value};" });
                                break;
                            case Parsing.Expressions.CreateNewNumber:
                                scope.Add(new FullBody { $"{Constants.classInstanceVariable}->{set.Property} = 0;" });
                                break;
                            default:
                                throw new FatalException();
                        }
                    }
                    break;
                case Parsing.EActiveScope.global:
                    {
                        var first = set.Statements.First();
                        switch (first)
                        {
                            case Parsing.Expressions.Bool @bool:
                                scope.Add(new FullBody { $"this->{set.Property} = {@bool.Value};" });
                                break;
                            case Parsing.Expressions.CreateNewBoolean:
                                scope.Add(new FullBody { $"this->{set.Property} = false;" });
                                break;
                            case Parsing.Expressions.Character @char:
                                scope.Add(new FullBody { $"this->{set.Property} = '{@char.Value}';" });
                                break;
                            case Parsing.Expressions.CreateNewCharacter:
                                scope.Add(new FullBody { $"this->{set.Property} = '\0';" });
                                break;
                            case Parsing.Expressions.Number number:
                                scope.Add(new FullBody { $"this->{set.Property} = {number.Value};" });
                                break;
                            case Parsing.Expressions.CreateNewNumber:
                                scope.Add(new FullBody { $"this->{set.Property} = 0;" });
                                break;
                            default:
                                throw new FatalException();
                        }
                    }
                    break;
                case Parsing.EActiveScope.auto:
                case Parsing.EActiveScope.local:
                    {
                        var first = set.Statements.First();
                        switch (first)
                        {
                            case Parsing.Expressions.Bool @bool:
                                scope.Add(new FullBody { $"{Constants.stateInstanceVariable}->{set.Property} = {@bool.Value};" });
                                break;
                            case Parsing.Expressions.CreateNewBoolean:
                                scope.Add(new FullBody { $"{Constants.stateInstanceVariable}->{set.Property} = false;" });
                                break;
                            case Parsing.Expressions.Character @char:
                                scope.Add(new FullBody { $"{Constants.stateInstanceVariable}->{set.Property} = '{@char.Value}';" });
                                break;
                            case Parsing.Expressions.CreateNewCharacter:
                                scope.Add(new FullBody { $"{Constants.stateInstanceVariable}->{set.Property} = '\0';" });
                                break;
                            case Parsing.Expressions.Number number:
                                scope.Add(new FullBody { $"{Constants.stateInstanceVariable}->{set.Property} = {number.Value};" });
                                break;
                            case Parsing.Expressions.CreateNewNumber:
                                scope.Add(new FullBody { $"{Constants.stateInstanceVariable}->{set.Property} = 0;" });
                                break;
                            default:
                                throw new FatalException();
                        }
                    }
                    break;
                default:
                    throw new NotImplementedException();
            }
            yield return scope;
        }
    }
}
