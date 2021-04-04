using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using XCG.Parsing;
using XCG.Validation;

namespace XCG.Generators.Cpp
{
    public class CppGenerator : IGenerator
    {
        private CppOptions Options { get; } = new CppOptions();
        public void Generate(Parser parser, string output)
        {
            var capturedSetters = parser.Setters.Where((q) => q.ActiveScope == EActiveScope.capture).ToArray();
            var instanceClass = new ClassDefinition("instance")
            {
                PrivateParts = new List<ICppPart>
                {
                    new ClassDefinition("resetable")
                    {
                        PublicParts = new List<ICppPart>
                        {
                            new FieldDefinition(new TypeImpl { Name = "m_ref", TypeString = "instance" }),
                            new FieldDefinition(new TypeImpl { Name = "m_contents", Type = EType.StringView }),
                            new FieldDefinition(new TypeImpl { Name = "m_file", Type = EType.String }),
                            new FieldDefinition(new TypeImpl { Name = "m_line", Type = EType.SizeT }),
                            new FieldDefinition(new TypeImpl { Name = "m_column", Type = EType.SizeT }),
                            new FieldDefinition(new TypeImpl { Name = "m_offset", Type = EType.SizeT }),
                            new MethodDefinition(EType.Void, "resetable", ": m_ref(ref)", new TypeImpl{ TypeString = "instance", ReferenceCount = 1, Name = "ref" })
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
                                    $@"ref.m_contents   = m_contents;",
                                    $@"ref.m_file       = m_file;",
                                    $@"ref.m_line       = m_line;",
                                    $@"ref.m_column     = m_column;",
                                    $@"ref.m_offset     = m_offset;",
                                }
                            }
                        }
                    },
                    new FullBody(EUsage.Header) { $@"friend class resetable;" },
                    new FieldDefinition(new TypeImpl { Name = "m_contents", Type = EType.StringView }),
                    new FieldDefinition(new TypeImpl { Name = "m_file", Type = EType.String }),
                    new FieldDefinition(new TypeImpl { Name = "m_line", Type = EType.SizeT }),
                    new FieldDefinition(new TypeImpl { Name = "m_column", Type = EType.SizeT }),
                    new FieldDefinition(new TypeImpl { Name = "m_offset", Type = EType.SizeT }),
                    new MethodDefinition(EType.Void, "skip")
                    {
                        new FullBody
                        {
                            @"while (m_contents.length() > m_offset)",
                            @"{",
                            @"    char c = m_contents[m_offset];",
                            @"    switch (c)",
                            @"    {",
                            @"        case '\r':",
                            @"        case '\t':",
                            @"        case ' ': m_column++; m_offset++; break;",
                            @"        case '\n': m_line++; m_column = 1; m_offset++; break;",
                            @"        default: return;",
                            @"    }",
                            @"}",
                        }
                    },
                    new MethodDefinition(EType.Boolean, "next")
                    {
                        new FullBody
                        {
                            @"if (m_contents.length() > m_offset)",
                            @"{",
                            @"    char c = m_contents[m_offset];",
                            @"    switch (c)",
                            @"    {",
                            @"        case '\r':",
                            @"        case '\t':",
                            @"        case ' ': m_column++; m_offset++; break;",
                            @"        case '\n': m_line++; m_column = 1; m_offset++; break;",
                            @"    }",
                            @"    return true;",
                            @"}",
                            @"else",
                            @"{",
                            @"    return false;",
                            @"}",
                        }
                    },
                    new MethodDefinition(EType.Char, "current")
                    {
                        new FullBody
                        {
                            @"if (m_contents.length() > m_offset)",
                            @"{",
                            @"    return m_contents[m_offset];",
                            @"}",
                            @"else",
                            @"{",
                            @"    return '\0';",
                            @"}",
                        }
                    }
                }
            };

            instanceClass.PrivateParts.AddRange(capturedSetters.Select((q) => new FieldDefinition(new TypeImpl
            {
                Name = q.Key.Replace('-', '_').ToLower(),
                Type = q.Statements.FirstOrDefault() switch
                {
                    Parsing.Expressions.CreateNewBoolean => EType.Boolean,
                    Parsing.Expressions.CreateNewNumber => EType.Float,
                    _ => throw new FatalException()
                }
            })));
            instanceClass.PrivateParts.AddRange(
                parser.Tokens.SelectMany((q) => q switch
                {
                    Parsing.Token token => token.ToParts(),
                    _ => throw new NotImplementedException(),
                }));


            System.IO.Directory.CreateDirectory(output);
            using (var writer = new System.IO.StreamWriter(System.IO.Path.Combine(output, Options.HeaderFileName)))
            {
                if (Options.NamespaceName is null)
                {
                    instanceClass.WriteHeader(this.Options, writer, String.Empty);
                }
                else
                {
                    var ns = new NamespaceDefinition(Options.NamespaceName)
                    {
                        instanceClass
                    };
                    ns.WriteHeader(this.Options, writer, String.Empty);
                }
            }
            using (var writer = new System.IO.StreamWriter(System.IO.Path.Combine(output, Options.ImplementationFileName)))
            {
                writer.WriteLine($@"#include ""{Options.HeaderFileName}""");
                if (Options.NamespaceName is null)
                {
                    instanceClass.WriteImplementation(this.Options, writer, String.Empty);
                }
                else
                {
                    var ns = new NamespaceDefinition(Options.NamespaceName)
                    {
                        instanceClass
                    };
                    ns.WriteImplementation(this.Options, writer, String.Empty);
                }
            }
        }

        public void RegisterRules(Validator validator)
        {
            validator.Register("CPP", ESeverity.Error, (parser) => {
                var hints = new List<Hint>();
                foreach (var setter in parser.Setters.Where((q) => q.ActiveScope == EActiveScope.capture))
                {
                    if (setter.Mode != EMode.SetProperty)
                    {
                        hints.Add(new Hint { File = setter.Diagnostics.File, Line = setter.Diagnostics.Line, Message = "Globally captured variables can only be set." });
                    }
                    else if (setter.Statements.Count != 1 || !setter.Statements.All((q) => q is Parsing.Expressions.CreateNewBoolean || q is Parsing.Expressions.CreateNewNumber))
                    {
                        hints.Add(new Hint { File = setter.Diagnostics.File, Line = setter.Diagnostics.Line, Message = "Globally captured variables must always be comprised of a single new expression." });
                    }
                }
                return hints;
            });
        }

        public void SetOption(string key, string? value)
        {
            var properties = Options.GetType().GetProperties(System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.Instance);
            var dict = properties.Select((q) => new
            {
                prop = q,
                att = q.GetCustomAttributes(true).Where((q) => q is CppOptionAttribute).Cast<CppOptionAttribute>().FirstOrDefault()
            }).Where((q) => q.att is not null).ToDictionary((q) => q.att!.Name.ToLower(), (q) => new { att = q.att!, q.prop });

            if (dict.TryGetValue(key.ToLower(), out var a))
            {
                if (!a.att.Nullable && value is null)
                {
                    throw new NullReferenceException($@"The option ""{a.att.Name}"" cannot be null.");
                }
                a.prop.SetValue(this.Options, value is null ? null : Convert.ChangeType(value, a.prop.PropertyType));
            }
            else
            {
                throw new KeyNotFoundException($@"The option ""{key}"" was not found.");
            }
        }
    }
}
