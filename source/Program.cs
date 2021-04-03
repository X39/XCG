using CommandLine;
using System;
using System.Collections.Generic;
using System.Linq;

namespace XCG
{
    internal class Program
    {
        private class CLIOptions
        {
            [Option('i', "input", Required = true, HelpText = "Declares a single input xcg file.", MetaValue = "PATH")]
            public IEnumerable<string>? Input { get; set; }

            [Option('g', "generator", Required = true, HelpText = "Sets the generator to use. Might be a path to a file or one of the build-in ones.", MetaValue = "GENERATOR")]
            public string? Generator { get; set; }

            [Option('o', "output", HelpText = "Set the output filepath to where the generated file(s) should be generated to.", MetaValue = "PATH", Default = "output")]
            public string? Output { get; set; }

            [Option('s', "set", HelpText = "Allows to change generator-dependant settings.", MetaValue = "OPTION:VALUE")]
            public IEnumerable<string>? Settings { get; set; }
        }

        private static void Colored(ESeverity severity, Action action)
        {
            switch (severity)
            {
                case ESeverity.Error:
                    Console.ForegroundColor = ConsoleColor.Red;
                    break;
                case ESeverity.Warning:
                    Console.ForegroundColor = ConsoleColor.Yellow;
                    break;
            }
            action();
            Console.ResetColor();
        }

        private static string SeverityString(ESeverity severity)
        {
            switch (severity)
            {
                case ESeverity.Error: return "ERR";
                case ESeverity.Warning: return "WRN";
                case ESeverity.Info: return "INF";
                default: return String.Empty;
            }
        }

        private static int Main(string[] args)
        {
            CLIOptions? cliOptions = null;
            var cliResult = Parser.Default.ParseArguments<CLIOptions>(args).WithParsed((options) => cliOptions = options);
            if (cliResult.Tag == ParserResultType.NotParsed || cliOptions is null)
            {
                return -1;
            }
            #region Parsing
            var parser = new Parsing.Parser();
            bool parseOk = true;
            foreach (string? s in cliOptions.Input ?? Array.Empty<string>())
            {
                string? filePath = System.IO.Path.GetFullPath(s);
                if (System.IO.File.Exists(filePath))
                {
                    string? contents = System.IO.File.ReadAllText(s);
                    bool parseResult = parser.Parse(filePath, contents, out var parseNotes);
                    foreach (var it in parseNotes)
                    {
                        Colored(it.Severity, () => Console.WriteLine(it.Message));
                    }
                    if (parseResult)
                    {
                        Console.BackgroundColor = ConsoleColor.Green;
                        Console.ForegroundColor = ConsoleColor.Black;
                        Console.WriteLine($"Parsing {filePath} ({s}) suceeded.");
                        Console.ResetColor();
                    }
                    else
                    {
                        Console.BackgroundColor = ConsoleColor.Red;
                        Console.ForegroundColor = ConsoleColor.White;
                        Console.Error.WriteLine($"Parsing {filePath} ({s}) failed.");
                        Console.ResetColor();
                        parseOk = false;
                    }
                }
                else
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.Error.WriteLine($"File not found: {filePath} ({s})");
                    Console.ResetColor();
                    parseOk = false;
                }
            }
            if (!parseOk)
            {
                Console.WriteLine();
                Console.BackgroundColor = ConsoleColor.Red;
                Console.ForegroundColor = ConsoleColor.White;
                Console.WriteLine("Aborting as errors have been encountered during parsing.");
                Console.ResetColor();
                return -1;
            }
            #endregion
            #region Fixup References
            int generatedReferences = 0;
            foreach (var reference in parser.References)
            {
                object? possibleActual;

                possibleActual = parser.Tokens.FirstOrDefault((q) => q.Alias == reference.Text);
                if (possibleActual is not null) { reference.Refered = possibleActual; continue; }

                possibleActual = parser.Tokens.FirstOrDefault((q) => q.Identifier == reference.Text);
                if (possibleActual is not null) { reference.Refered = possibleActual; continue; }

                possibleActual = parser.Productions.FirstOrDefault((q) => q.Identifier == reference.Text);
                if (possibleActual is not null) { reference.Refered = possibleActual; continue; }

                var token = new Parsing.Token
                {
                    Alias = reference.Text,
                    Identifier = $"@auto-{++generatedReferences}",
                    Statements = new List<Parsing.ITokenStatement>
                    {
                        new Parsing.TokenStatements.Require
                        {
                            Negated = false,
                            Range = new Parsing.Multiplicity(1, new Parsing.Diagnostic { Column = 0, File = "---auto-generated---", Line = 0, Offset = 0 }),
                            Parts = new List<Parsing.IPart>
                            {
                                new Parsing.Word(reference.Text)
                            }
                        }
                    }
                };
                reference.Refered = token;
                parser.Tokens.Add(token);
            }
            #endregion
            #region Create Generator
            // Pick the correct generator
            IGenerator? generator = null;
            switch (cliOptions.Generator?.ToLower())
            {
                case "cpp":
                case "c++":
                    generator = new Generators.CppGenerator();
                    break;
                case null: return -1;
                default:
                    string? generatorAbsolute = System.IO.Path.GetFullPath(cliOptions.Generator);
                    if (System.IO.File.Exists(generatorAbsolute))
                    {
                        try
                        {
                            var reflectionOnlyAssembly = System.Reflection.Assembly.ReflectionOnlyLoadFrom(generatorAbsolute);
                            if (reflectionOnlyAssembly.GetExportedTypes().Any((t) => t.IsAssignableTo(typeof(IGenerator))))
                            {
                                var assembly = System.Reflection.Assembly.Load(generatorAbsolute);
                                var generatorType = assembly.GetExportedTypes().First((t) => t.IsAssignableFrom(typeof(IGenerator)));
                                try
                                {
                                    generator = (IGenerator)Activator.CreateInstance(generatorType)!;
                                }
                                catch (Exception ex)
                                {
                                    Console.BackgroundColor = ConsoleColor.Red;
                                    Console.ForegroundColor = ConsoleColor.White;
                                    Console.WriteLine($"Failed to create instance of IGenerator with {generatorAbsolute} ({cliOptions.Generator}):");
                                    Console.WriteLine(ex.Message);
                                    Console.ResetColor();
                                    return -1;
                                }
                            }
                            else
                            {
                                Console.BackgroundColor = ConsoleColor.Red;
                                Console.ForegroundColor = ConsoleColor.White;
                                Console.WriteLine($"Assembly {generatorAbsolute} ({cliOptions.Generator}) is not containing a usible IGenerator implementation.");
                                Console.ResetColor();
                            }
                        }
                        catch (Exception ex)
                        {
                            Console.BackgroundColor = ConsoleColor.Red;
                            Console.ForegroundColor = ConsoleColor.White;
                            Console.WriteLine($"Failed to load assembly {generatorAbsolute} ({cliOptions.Generator}):");
                            Console.WriteLine(ex.Message);
                            Console.ResetColor();
                            return -1;
                        }
                    }
                    else
                    {
                        Console.BackgroundColor = ConsoleColor.Red;
                        Console.ForegroundColor = ConsoleColor.White;
                        Console.WriteLine($"File {generatorAbsolute} ({cliOptions.Generator}) not found.");
                        Console.ResetColor();
                    }
                    return -1;
            }

            // Set generator options
            foreach (string? option in cliOptions.Settings ?? Array.Empty<string>())
            {
                string[]? splitted = option.Split(':');
                string? key = splitted[0];
                string? value = splitted.Length >= 2 ? splitted[1] : null;
                generator.SetOption(key, value);
            }
            #endregion
            #region Validation
            var validator = new Validation.Validator();
            RegisterDefaultValidatorRules(validator);
            generator.RegisterRules(validator);

            if (!validator.Validate(parser, (rule, hint) => Colored(rule.Severity,
                () => Console.WriteLine($"[{rule.Realm}{rule.Code}][{SeverityString(rule.Severity)}][{hint.File}][{hint.Line}]: {hint.Message}"))))
            {
                return -1;
            }
            #endregion

            // Tell the generator to generate the parser
            generator.Generate(parser, cliOptions.Output ?? System.Environment.CurrentDirectory);
            return 0;
        }

        private static void RegisterDefaultValidatorRules(Validation.Validator validator)
        {
            validator.Register("V", ESeverity.Warning, (parser) =>
            {
                var hints = new List<Validation.Hint>();
                var identifiers = new HashSet<string>();
                foreach (var token in parser.Tokens)
                {
                    if (identifiers.Contains(token.Identifier))
                    {
                        hints.Add(new Validation.Hint
                        {
                            File = token.Diagnostics.File,
                            Line = token.Diagnostics.Line,
                            Message = $@"Identifier of token ""{token.Identifier}"" collides with token existing identifier"
                        });
                    }
                    else
                    {
                        identifiers.Add(token.Identifier);
                    }
                }
                foreach (var production in parser.Productions)
                {
                    if (identifiers.Contains(production.Identifier))
                    {
                        hints.Add(new Validation.Hint
                        {
                            File = production.Diagnostics.File,
                            Line = production.Diagnostics.Line,
                            Message = $@"Identifier of production ""{production.Identifier}"" collides with token existing identifier"
                        });
                    }
                    else
                    {
                        identifiers.Add(production.Identifier);
                    }
                }
                return hints;
            });
            validator.Register("V", ESeverity.Warning, (parser) =>
            {
                var hints = new List<Validation.Hint>();
                var identifiers = parser.Tokens.Select((q) => q.Identifier).Concat(parser.Productions.Select((q) => q.Identifier)).Distinct().ToHashSet();
                foreach (var token in parser.Tokens)
                {
                    if (identifiers.Contains(token.Alias))
                    {
                        hints.Add(new Validation.Hint
                        {
                            File = token.Diagnostics.File,
                            Line = token.Diagnostics.Line,
                            Message = $@"Alias ""{token.Alias}"" collides with token existing identifier"
                        });
                    }
                }
                return hints;
            });
        }
    }
}
