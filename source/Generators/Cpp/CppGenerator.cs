using System;
using System.Collections.Generic;
using System.Linq;
using XCG.Generators.Cpp.Extensive;
using XCG.Parsing;
using XCG.Validation;

namespace XCG.Generators.Cpp
{
    public class CppGenerator : IGenerator
    {
        private CppOptions Options { get; } = new();

        public void Generate(Parser parser, string output)
        {
            var capturedSetters = parser.Setters.Where((q) => q.ActiveScope == EActiveScope.capture).ToArray();
            var mainProduction = parser.Productions.First((q) => q.Identifier == "main");
            var instanceClass = new ClassDefinition(string.Concat(Options.TypePrefix, Options.ClassName))
            {
                PublicParts = new List<ICppPart>
                {
                    new MethodDefinition(string.Empty, string.Concat(Options.TypePrefix, Options.ClassName),
                        " : m_contents(contents), m_file(file), m_line(1), m_column(1), m_offset(0)",
                        new ArgImpl {Type = EType.StringView, Name = "contents"},
                        new ArgImpl {Type = EType.String, Name = "file"})
                    {
                        HeaderOnly = true
                    },
                    new EnumDefinition(string.Concat(Options.TypePrefix, Options.TokenEnumName))
                    {
                        Entries = parser.Tokens.Select((q) => q.GetCppEnumName()).ToList()
                    },
                    new ClassDefinition(string.Concat(Options.TypePrefix, Options.TokenName))
                    {
                        PublicParts = new List<ICppPart>
                        {
                            new FieldDefinition(new ArgImpl
                                {Name = "type", TypeString = string.Concat(Options.TypePrefix, Options.TokenEnumName)}),
                            new FieldDefinition(new ArgImpl {Name = "file", Type = EType.String}),
                            new FieldDefinition(new ArgImpl {Name = "line", Type = EType.SizeT}),
                            new FieldDefinition(new ArgImpl {Name = "column", Type = EType.SizeT}),
                            new FieldDefinition(new ArgImpl {Name = "offset", Type = EType.SizeT}),
                            new FieldDefinition(new ArgImpl {Name = "length", Type = EType.SizeT}),
                        }
                    },
                    new MethodDefinition(
                        string.Concat(Options.RootClassName, Options.TypePrefix, Options.TokenName),
                        "create_token",
                        new ArgImpl {Type = EType.SizeT, Name = "length"},
                        new ArgImpl
                        {
                            TypeString = string.Concat(Options.TypePrefix, Options.TokenEnumName), Name = "type"
                        })
                    {
                        $@"{string.Concat(Options.TypePrefix, Options.TokenName)} t;",
                        $@"t.file = m_file;",
                        $@"t.line = m_line;",
                        $@"t.column = m_column;",
                        $@"t.offset = m_offset;",
                        $@"t.length = length;",
                        $@"t.type = type;",
                        $@"for (auto i = 0; i < length; i++)",
                        $@"{{",
                        $@"    next();",
                        $@"}}",
                        $@"return t;",
                    }
                },
                ProtectedParts = new List<ICppPart>
                {
                    new FieldDefinition(new ArgImpl {Name = "m_contents", Type = EType.StringView}),
                    new FieldDefinition(new ArgImpl {Name = "m_file", Type = EType.String}),
                    new FieldDefinition(new ArgImpl {Name = "m_line", Type = EType.SizeT}),
                    new FieldDefinition(new ArgImpl {Name = "m_column", Type = EType.SizeT}),
                    new FieldDefinition(new ArgImpl {Name = "m_offset", Type = EType.SizeT}),
                    new MethodDefinition(EType.Void, "report", new ArgImpl {Name = "message", Type = EType.StringView},
                        new ArgImpl {Name = "depth", Type = EType.SizeT})
                    {
                        IsVirtual = true,
                        Parts = new List<ICppPart>
                        {
                            new FullBody
                            {
                                $@"std::cout << ""[L"" << m_line << ""]"" << ""[C"" << m_column << ""] "" << message << ""\n"";"
                            }
                        }
                    },
                    new DebugPart
                    {
                        new MethodDefinition(EType.Void, "trace",
                            new ArgImpl {Name = "message", Type = EType.StringView},
                            new ArgImpl {Name = "depth", Type = EType.SizeT})
                        {
                            IsVirtual = true,
                            Parts = new List<ICppPart>
                            {
                                new FullBody
                                {
                                    $@"std::cout << std::string(depth, ' ') << ""[L"" << m_line << ""]"" << ""[C"" << m_column << ""] "" << message << ""\n"";"
                                }
                            }
                        }
                    }
                },
                PrivateParts = new List<ICppPart>
                {
                    new ClassDefinition("resettable")
                    {
                        PublicParts = new List<ICppPart>
                        {
                            new FieldDefinition(new ArgImpl
                            {
                                Name = "m_ref", ReferenceCount = 1,
                                TypeString = string.Concat(Options.TypePrefix, Options.ClassName)
                            }),
                            new FieldDefinition(new ArgImpl {Name = "m_contents", Type = EType.StringView}),
                            new FieldDefinition(new ArgImpl {Name = "m_file", Type = EType.String}),
                            new FieldDefinition(new ArgImpl {Name = "m_line", Type = EType.SizeT}),
                            new FieldDefinition(new ArgImpl {Name = "m_column", Type = EType.SizeT}),
                            new FieldDefinition(new ArgImpl {Name = "m_offset", Type = EType.SizeT}),
                            new MethodDefinition(EType.None, "resettable", ": m_ref(ref)",
                                new ArgImpl
                                {
                                    TypeString = string.Concat(Options.TypePrefix, Options.ClassName),
                                    ReferenceCount = 1, Name = "ref"
                                })
                            {
                                new FullBody
                                {
                                    $@"m_contents = ref.m_contents;",
                                    $@"m_file = ref.m_file;",
                                    $@"m_line = ref.m_line;",
                                    $@"m_column = ref.m_column;",
                                    $@"m_offset = ref.m_offset;",
                                }
                            },
                            new MethodDefinition(EType.Void, "reset")
                            {
                                new FullBody
                                {
                                    $@"m_ref.m_contents   = m_contents;",
                                    $@"m_ref.m_file       = m_file;",
                                    $@"m_ref.m_line       = m_line;",
                                    $@"m_ref.m_column     = m_column;",
                                    $@"m_ref.m_offset     = m_offset;",
                                }
                            }
                        }
                    },
                    new FullBody(EUsage.Header) {$@"friend class resettable;"},
                    new MethodDefinition(EType.Boolean, "next")
                    {
                        new IfPart(IfPart.EIfScope.If, "m_contents.length() > m_offset")
                        {
                            new VariableDefinition(EType.Char, "c", "m_contents[m_offset]"),
                            @"switch (c)",
                            @"{",
                            @"    case '\r':",
                            @"    case '\t':",
                            @"    case ' ':",
                            @"    default: m_column++; m_offset++; break;",
                            @"    case '\n': m_line++; m_column = 1; m_offset++; break;",
                            @"}",
                            new ReturnPart(EValueConstant.True)
                        },
                        new IfPart(IfPart.EIfScope.Else, null)
                        {
                            new ReturnPart(EValueConstant.False)
                        }
                    },
                    new MethodDefinition(EType.Char, "current")
                    {
                        new IfPart(IfPart.EIfScope.If, "m_contents.length() > m_offset")
                        {
                            new ReturnPart("m_contents[m_offset]"),
                        },
                        new IfPart(IfPart.EIfScope.Else, null)
                        {
                            new ReturnPart(EValueConstant.NullChar),
                        }
                    }
                }
            };


            var captureClasses = Array.Empty<IStatement>()
                .Concat(parser.Productions)
                .Concat(parser.LeftRecursiveItems)
                .Select((q) => q.GetClassDefinition(Options))
                .NotNull()
                .ToArray();
            var stateClasses = Array.Empty<IStatement>()
                .Concat(parser.Productions)
                .Concat(parser.LeftRecursiveItems)
                .Select((q) => q.GetStateDefinition(Options))
                .NotNull()
                .ToArray();
            instanceClass.PublicParts.AddRange(captureClasses);
            instanceClass.PublicParts.AddRange(stateClasses);

            instanceClass.PrivateParts.AddRange(capturedSetters.Select((q) => new FieldDefinition(new ArgImpl
            {
                Name = q.Key.Replace('-', '_').ToLower(),
                Type = q.Children.FirstOrDefault() switch
                {
                    Parsing.Expressions.CreateNewBoolean => EType.Boolean,
                    Parsing.Expressions.CreateNewNumber => EType.Float,
                    _ => throw new FatalException()
                }
            })));
            instanceClass.PrivateParts.AddRange(
                Array.Empty<object>()
                    .Concat(parser.Tokens)
                    .Concat(parser.Productions)
                    .Concat(parser.LeftRecursiveItems)
                    .SelectMany((q) => q switch
                    {
                        LeftRecursive leftRecursive => leftRecursive.ToParts(Options),
                        Production production => production.ToParts(Options),
                        Token token => token.ToParts(Options),
                        _ => throw new NotImplementedException(),
                    }).Distinct());

            instanceClass.PublicParts.Add(
                new MethodDefinition(mainProduction.ToCppTypeName(Options, true).ToCppSharedPtrType(), "parse")
                {
                    $@"skip();",
                    $@"return {mainProduction.ToCppMatchMethodName(Options)}(0);"
                });
            instanceClass.PublicParts.AddRange(parser.Productions
                .SelectMany((q) => q.FindChildren<Parsing.Statements.Set>())
                .Where((q) => q.ActiveScope == EActiveScope.global)
                .GroupBy((q) => q.Key)
                .Select((g) => new CaptureDefinition(g.Key, g.Select((q) => q.ToTypeImpl(Options)))));

            if (Options.CreateStringTree)
            {
                instanceClass.PublicParts.AddRange(captureClasses.Select((q) =>
                    q.CreatePrintTreeMethodDefinition(Options)));
            }

            if (Options.CreateVisitor)
            {
                var visitorClass = new ClassDefinition("visitor");
                visitorClass.ProtectedParts.AddRange(
                    captureClasses.Select((q) =>
                    {
                        var methodDefinition = new MethodDefinition(
                            EType.Boolean,
                            string.Concat(Options.MethodsPrefix, "visit_enter"),
                            new ArgImpl {Name = "node", TypeString = q.FullName.ToCppSharedPtrType()})
                        {
                            new ReturnPart(EValueConstant.True),
                        };
                        methodDefinition.IsVirtual = true;
                        return methodDefinition;
                    }));
                visitorClass.ProtectedParts.AddRange(
                    captureClasses.Select((q) =>
                    {
                        var methodDefinition = new MethodDefinition(
                            EType.Boolean,
                            string.Concat(Options.MethodsPrefix, "visit_leave"),
                            new ArgImpl {Name = "node", TypeString = q.FullName.ToCppSharedPtrType()})
                        {
                            new ReturnPart(EValueConstant.True),
                        };
                        methodDefinition.IsVirtual = true;
                        return methodDefinition;
                    }));
                visitorClass.PublicParts.AddRange(captureClasses.Where((q) => q.Name == "main")
                    .Select((q) => q.CreateVisitTreeMethodDefinition(Options)));
                visitorClass.PrivateParts.AddRange(captureClasses.Where((q) => q.Name != "main")
                    .Select((q) => q.CreateVisitTreeMethodDefinition(Options)));
                instanceClass.PublicParts.Add(visitorClass);
            }

            instanceClass.PrivateParts.Add(GetSkipMethod(parser));
            System.IO.Directory.CreateDirectory(output);
            using (var writer = new System.IO.StreamWriter(System.IO.Path.Combine(output, Options.HeaderFileName)))
            {
                var guardName = string.Concat("INCLUDE_GUARD_", Options.ImplementationFileName.Replace('.', '_'),
                    Options.TypePrefix, "_", Options.ClassName).ToUpper();
                writer.WriteLine($@"#ifndef {guardName}");
                writer.WriteLine($@"#define {guardName}");
                writer.WriteLine($@"#include <memory>");
                writer.WriteLine($@"#include <string>");
                writer.WriteLine($@"#include <string_view>");
                writer.WriteLine($@"#include <optional>");
                writer.WriteLine($@"#include <variant>");
                writer.WriteLine($@"#include <sstream>");
                writer.WriteLine($@"#include <vector>");
                writer.WriteLine();
                if (Options.NamespaceName is null)
                {
                    instanceClass.WriteHeader(Options, writer, string.Empty);
                }
                else
                {
                    var ns = new NamespaceDefinition(Options.NamespaceName)
                    {
                        instanceClass
                    };
                    ns.WriteHeader(Options, writer, string.Empty);
                }

                writer.WriteLine($@"#endif // {guardName}");
            }

            using (var writer =
                new System.IO.StreamWriter(System.IO.Path.Combine(output, Options.ImplementationFileName)))
            {
                writer.WriteLine($@"#include ""{Options.HeaderFileName}""");
                writer.WriteLine($@"#include <iostream>");
                writer.WriteLine();
                if (Options.NamespaceName is null)
                {
                    instanceClass.WriteImplementation(Options, writer, string.Empty);
                }
                else
                {
                    var ns = new NamespaceDefinition(Options.NamespaceName)
                    {
                        instanceClass
                    };
                    ns.WriteImplementation(Options, writer, string.Empty);
                }
            }
        }

        private static MethodDefinition GetSkipMethod(Parser parser)
        {
            var localsCount = 0;
            string ToUnique(string str) => string.Concat(str, (++localsCount).ToString());

            var scopePart = new ScopePart();
            var method = new MethodDefinition(EType.Void, "skip")
            {
                new WhilePart("m_contents.length() > m_offset")
                {
                    new VariableDefinition(EType.Char, "c", "m_contents[m_offset]"),
                    @"switch (c)",
                    new ScopePart
                    {
                        @"case '\r':",
                        @"case '\t':",
                        @"case ' ': m_column++; m_offset++; break;",
                        @"case '\n': m_line++; m_column = 1; m_offset++; break;",
                        @"default:",
                        scopePart,
                    }
                }
            };
            var wasMatchedVariable = ToUnique("wasMatched");
            scopePart.Add(new VariableDefinition(EType.Boolean, wasMatchedVariable, "false"));
            foreach (var comment in parser.Comments)
            {
                var start = comment.Start!.ToLower() switch
                {
                    "eof" => "\0",
                    "eol" => "\n",
                    _ => comment.Start!
                };
                var end = comment.End!.ToLower() switch
                {
                    "eof" => "\0",
                    "eol" => "\n",
                    _ => comment.End!
                };
                var indexVariable = ToUnique("i");
                var ifPart = new IfPart(
                    IfPart.EIfScope.If,
                    string.Concat(
                        $@"m_contents.length() > m_offset + {start.Length} && ",
                        string.Join(" && ", start.Select((c, i) => $@"m_contents[m_offset + {i}] == '{c.Escape()}'"))
                    ))
                {
                    $@"{wasMatchedVariable} = true;",
                    $@"for (size_t {indexVariable} = 0; {indexVariable} < {start.Length}; {indexVariable}++)",
                    new ScopePart
                    {
                        @"switch (m_contents[m_offset])",
                        new ScopePart
                        {
                            @"case '\r':",
                            @"case '\t':",
                            @"case ' ': m_column++; m_offset++; break;",
                            @"case '\n': m_line++; m_column = 1; m_offset++; break;",
                            @"default: m_column++; m_offset++; break;"
                        }
                    },
                    new WhilePart(string.Concat(
                        $@"m_contents.length() > m_offset + {start.Length} && !(",
                        string.Join(" && ", end.Select((c, i) => $@"m_contents[m_offset + {i}] == '{c.Escape()}'")),
                        ")"
                    ))
                    {
                        @"switch (m_contents[m_offset])",
                        new ScopePart
                        {
                            @"case '\r':",
                            @"case '\t':",
                            @"case ' ': m_column++; m_offset++; break;",
                            @"case '\n': m_line++; m_column = 1; m_offset++; break;",
                            @"default: m_column++; m_offset++; break;"
                        }
                    },
                    $@"for (size_t {indexVariable} = 0; {indexVariable} < {end.Length}; {indexVariable}++)",
                    new ScopePart
                    {
                        @"switch (m_contents[m_offset])",
                        new ScopePart
                        {
                            @"case '\r':",
                            @"case '\t':",
                            @"case ' ': m_column++; m_offset++; break;",
                            @"case '\n': m_line++; m_column = 1; m_offset++; break;",
                            @"default: m_column++; m_offset++; break;"
                        }
                    },
                };
                scopePart.Add(ifPart);
            }

            scopePart.Add(new IfPart(IfPart.EIfScope.If, string.Concat('!', wasMatchedVariable))
            {
                $@"return;",
            });
            return method;
        }

        public void RegisterRules(Validator validator)
        {
            validator.Register("CPP", ESeverity.Error, (parser) =>
            {
                var hints = new List<Hint>();
                foreach (var setter in Array.Empty<IStatement>()
                    .Concat(parser.Productions)
                    .Concat(parser.LeftRecursiveItems)
                    .SelectMany((q) => q.FindChildren<Parsing.Statements.Set>())
                    .Concat(parser.Setters)
                    .Where((q) => q.ActiveScope == EActiveScope.capture))
                {
                    if (setter.Mode != EMode.SetProperty)
                    {
                        hints.Add(new Hint
                        {
                            File = setter.Diagnostics.File, Line = setter.Diagnostics.Line,
                            Message = "Set with capture scope cannot must set a property directly."
                        });
                    }
                }

                return hints;
            });
            validator.Register("CPP", ESeverity.Error, (parser) =>
            {
                var hints = new List<Hint>();
                foreach (var setter in Array.Empty<IStatement>()
                    .Concat(parser.Productions)
                    .Concat(parser.LeftRecursiveItems)
                    .SelectMany((q) => q.FindChildren<Parsing.Statements.Set>())
                    .Concat(parser.Setters)
                    .Where((q) => q.ActiveScope == EActiveScope.capture))
                {
                    if (setter.Children.Count != 1
                        || !setter.Children.All((q) => q switch
                        {
                            Parsing.Expressions.CreateNewBoolean => true,
                            Parsing.Expressions.Bool => true,
                            Parsing.Expressions.CreateNewCharacter => true,
                            Parsing.Expressions.Character => true,
                            Parsing.Expressions.CreateNewNumber => true,
                            Parsing.Expressions.Number => true,
                            _ => false
                        }))
                    {
                        hints.Add(new Hint
                        {
                            File = setter.Diagnostics.File, Line = setter.Diagnostics.Line,
                            Message = "Set with capture scope must always be comprised of a single expression."
                        });
                    }
                }

                return hints;
            });
        }

        public void SetOption(string key, string? value)
        {
            var properties = Options.GetType()
                .GetProperties(System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.Instance);
            var dict = properties.Select((q) => new
                {
                    att = q.GetCustomAttributes(true).OfType<CppOptionAttribute>()
                        .FirstOrDefault(),
                    prop = q
                }).Where((q) => q.att is not null)
                .ToDictionary((q) => q.att!.Name.ToLower(), (q) => new {att = q.att!, q.prop});

            if (dict.TryGetValue(key.ToLower(), out var a))
            {
                if (!a.att.Nullable && value is null)
                {
                    throw new NullReferenceException($@"The option ""{a.att.Name}"" cannot be null.");
                }

                a.prop.SetValue(Options, value is null ? null : Convert.ChangeType(value, a.prop.PropertyType));
            }
            else
            {
                throw new KeyNotFoundException($@"The option ""{key}"" was not found.");
            }
        }

        public IEnumerable<(string option, object? value)> GetOptions()
        {
            var properties = Options.GetType()
                .GetProperties(System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.Instance);
            return properties.Select((q) => new
                {
                    prop = q,
                    att = q.GetCustomAttributes(true).OfType<CppOptionAttribute>()
                        .FirstOrDefault()
                }).Where((q) => q.att is not null)
                .Select((q) => (option: q.att!.Name.ToLower(), value: q.prop.GetValue(Options)));
        }
    }
}