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

        private static string? ToStringRepresentation(char c)
        {
            return c switch
            {
                '\\' => "back-slash",
                '\'' => "single-quotation",
                '$' => "dollar",
                '*' => "star",
                '/' => "slash",
                '+' => "plus",
                '-' => "minus",
                '_' => "underscore",
                '!' => "exclamation",
                '?' => "question",
                '~' => "tilde",
                '.' => "dot",
                ',' => "comma",
                '"' => "double-quotation",
                '|' => "vertical-bar",
                '&' => "ampersand",
                '^' => "circumflex",
                '%' => "percent",
                '§' => "paragraph",
                '=' => "equal",
                ':' => "colon",
                '#' => "hash",
                '°' => "degree",
                '<' => "less-then",
                '>' => "greater-then",
                '(' => "round-bracked-open",
                ')' => "round-bracked-close",
                '[' => "square-bracked-open",
                ']' => "square-bracked-close",
                '{' => "curly-bracked-open",
                '}' => "curly-bracked-close",
                _ => null,
            };
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
                generatedReferences++;
                if (reference.CaptureName is null)
                {
                    reference.CaptureName =  $"capture{generatedReferences}";
                }
                object? possibleActual;

                possibleActual = parser.Tokens.FirstOrDefault((q) => q.Alias == reference.Text);
                if (possibleActual is not null) { reference.Refered = possibleActual; continue; }

                possibleActual = parser.Tokens.FirstOrDefault((q) => q.Identifier == reference.Text);
                if (possibleActual is not null) { reference.Refered = possibleActual; continue; }

                possibleActual = parser.Productions.FirstOrDefault((q) => q.Identifier == reference.Text);
                if (possibleActual is not null) { reference.Refered = possibleActual; continue; }

                possibleActual = parser.LeftRecursives.FirstOrDefault((q) => q.Identifier == reference.Text);
                if (possibleActual is not null) { reference.Refered = possibleActual; continue; }

                string identifier;
                if (reference.Text.All((c) => ToStringRepresentation(c) != null))
                {
                    identifier = string.Concat("@", String.Join("-", reference.Text.Select(ToStringRepresentation)));
                }
                else if(reference.Text.All((c) => char.IsLetterOrDigit(c) || c == '-'))
                {
                    identifier = String.Concat("@", reference.Text.ToLower());
                }
                else
                {
                    identifier = $"@auto-{generatedReferences}";
                }
                var token = new Parsing.Token
                {
                    Alias = reference.Text,
                    Identifier = identifier,
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
                    generator = new Generators.Cpp.CppGenerator();
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
            bool optionError = false;
            foreach (string? option in cliOptions.Settings ?? Array.Empty<string>())
            {
                string key = String.Empty;
                string? value = null;
                var splitterIndex = option.IndexOf(':');
                if (splitterIndex == -1)
                {
                    key = option;
                }
                else
                {
                    key = option[..splitterIndex];
                    value = option[(splitterIndex + 1)..];
                }
                try
                {
                    generator.SetOption(key, value);
                }
                catch (Exception ex)
                {
                    Console.ForegroundColor = ConsoleColor.Red;
                    Console.Error.WriteLine(String.Concat(ex.GetType().Name, ": ", ex.Message));
                    Console.ResetColor();
                    optionError = true;
                }
            }
            if (optionError)
            {
                Console.BackgroundColor = ConsoleColor.Red;
                Console.ForegroundColor = ConsoleColor.White;
                Console.WriteLine($"Aborting generation as options have not been set successfully.");
                Console.ResetColor();
                return -1;
            }
            #endregion
            #region Validation
            var validator = new Validation.Validator();
            RegisterDefaultValidatorRules(validator);
            generator.RegisterRules(validator);

            if (!validator.Validate(parser, (rule, hint) => Colored(rule.Severity,
                () => Console.WriteLine($"[{rule.Realm}{rule.Code:0000}][{SeverityString(rule.Severity)}][{hint.File}][L{hint.Line}]: {hint.Message}"))))
            {
                return -1;
            }
            #endregion

            // Tell the generator to generate the parser
            string? outputPath = System.IO.Path.GetFullPath(cliOptions.Output ?? System.Environment.CurrentDirectory);
            try
            {
                generator.Generate(parser, outputPath);
                return 0;
            }
            catch (NotImplementedException ex)
            {
                Console.BackgroundColor = ConsoleColor.DarkRed;
                Console.ForegroundColor = ConsoleColor.White;
                Console.WriteLine(ex.FullStackTrace());
                Console.ResetColor();

                Console.ForegroundColor = ConsoleColor.Cyan;
                Console.WriteLine("Looks like you found a pattern that is not yet implemented.");
                Console.WriteLine("XCG is not a finished product.");
                Console.WriteLine("Either try to use a different pattern,");
                Console.WriteLine("or raise an issue (or comment under some existing with your pattern) at https://github.com/X39/XCG.");
                Console.WriteLine("Sorry for the inconvenience.");
                Console.ResetColor();
                return -1;
            }
            catch (FatalException ex)
            {
                Console.BackgroundColor = ConsoleColor.DarkRed;
                Console.ForegroundColor = ConsoleColor.White;
                Console.WriteLine(ex.FullStackTrace());
                Console.ResetColor();

                Console.ForegroundColor = ConsoleColor.Cyan;
                Console.WriteLine("A Fatal Exception got raised.");
                Console.WriteLine("This should never, ever happen!");
                Console.WriteLine("Please raise an issue with:");
                Console.WriteLine("- All input files used");
                Console.WriteLine("- The exact CLI args passed");
                Console.WriteLine("- The entirety of this consoles output");
                Console.WriteLine("at https://github.com/X39/XCG so it can be fixed ASAP.");
                Console.ResetColor();
                return -1;
            }
            catch (Exception ex)
            {
                Console.BackgroundColor = ConsoleColor.DarkRed;
                Console.ForegroundColor = ConsoleColor.White;
                Console.WriteLine(ex.FullStackTrace());
                Console.ResetColor();

                Console.ForegroundColor = ConsoleColor.Cyan;
                Console.WriteLine("Something moved wrong during generation.");
                Console.WriteLine("Please raise an issue at https://github.com/X39/XCG so it can be fixed.");
                Console.WriteLine("Sorry for the inconvenience.");
                Console.ResetColor();
                return -1;
            }
        }

        private static void RegisterDefaultValidatorRules(Validation.Validator validator)
        {
            // Identifier Collision
            validator.Register("XCG", ESeverity.Warning, (parser) =>
            {
                var hints = new List<Validation.Hint>();
                var identifiers = parser.Tokens.Select((q) => q.Identifier)
                .Concat(parser.Productions.Select((q) => q.Identifier))
                .Concat(parser.LeftRecursives.Select((q) => q.Identifier))
                .Concat(parser.Messages.Select((q) => q.Identifier))
                .GroupBy((q) => q)
                .Where((q) => q.Count() > 1)
                .Select((q) => q.Key)
                .ToHashSet();
                foreach (var tuple in parser.Tokens.Select((q) => (diag: q.Diagnostics, ident: q.Identifier))
                .Concat(parser.Productions.Select((q) => (diag: q.Diagnostics, ident: q.Identifier)))
                .Concat(parser.LeftRecursives.Select((q) => (diag: q.Diagnostics, ident: q.Identifier)))
                .Concat(parser.Messages.Select((q) => (diag: q.Diagnostics, ident: q.Identifier))))
                {
                    if (identifiers.Contains(tuple.ident))
                    {
                        hints.Add(new Validation.Hint
                        {
                            File = tuple.diag.File,
                            Line = tuple.diag.Line,
                            Message = $@"Identifier ""{tuple.ident}"" collides with existing identifier"
                        });
                    }
                }
                return hints;
            });
            // Alias Collision
            validator.Register("XCG", ESeverity.Warning, (parser) =>
            {
                var hints = new List<Validation.Hint>();
                var identifiers = parser.Tokens.Select((q) => q.Identifier)
                .Concat(parser.Tokens.Select((q) => q.Alias).Where((q) => !String.IsNullOrWhiteSpace(q)))
                .Concat(parser.Productions.Select((q) => q.Identifier))
                .Concat(parser.LeftRecursives.Select((q) => q.Identifier))
                .Concat(parser.Messages.Select((q) => q.Identifier))
                .GroupBy((q) => q)
                .Where((q) => q.Count() > 1)
                .Select((q) => q.Key)
                .ToHashSet();
                foreach (var token in parser.Tokens)
                {
                    if (identifiers.Contains(token.Alias))
                    {
                        hints.Add(new Validation.Hint
                        {
                            File = token.Diagnostics.File,
                            Line = token.Diagnostics.Line,
                            Message = $@"Alias ""{token.Alias}"" collides with existing identifier or alias"
                        });
                    }
                }
                return hints;
            });
            // Ensure token parts only refer to tokens
            validator.Register("XCG", ESeverity.Error, (parser) =>
            {
                var hints = new List<Validation.Hint>();
                var identifiers = parser.Tokens.Select((q) => q.Identifier).Concat(parser.Productions.Select((q) => q.Identifier)).Distinct().ToHashSet();
                foreach (var token in parser.Tokens)
                {
                    foreach (var it in token.Statements)
                    {
                        List<Parsing.IPart> parts;
                        if (it is Parsing.TokenStatements.Require require)
                        {
                            parts = require.Parts;
                        }
                        else if (it is Parsing.TokenStatements.Backtrack backtrack)
                        {
                            parts = backtrack.Parts;
                        }
                        else
                        {
                            throw new FatalException("Missing TokenStatement implementation");
                        }
                        foreach (var reference in parts.Where((q) => q is Parsing.Reference).Cast<Parsing.Reference>())
                        {
                            if (reference.Refered is not Parsing.Token)
                            {
                                hints.Add(new Validation.Hint
                                {
                                    File = token.Diagnostics.File,
                                    Line = token.Diagnostics.Line,
                                    Message = $@"Expected reference to refer to a token."
                                });
                            }
                        }
                    }
                }
                return hints;
            });
            // Left-recursion in production at top level
            validator.Register("XCG", ESeverity.Error, (parser) =>
            {
                var hints = new List<Validation.Hint>();
                var recursiveMatches = (from q in parser.Productions
                                        where q.Statements.Any()
                                        select (q.Statements.First() switch
                                        {
                                            Parsing.Statements.Alternatives alternatives => alternatives.Matches
                                            .Where((q2) => q2.Parts.First() is Parsing.Reference),
                                            Parsing.Statements.Match match => match.Parts.First() is Parsing.Reference reference
                                            && reference.Refered == q ? new[] { match } : Array.Empty<Parsing.Statements.Match>(),
                                            _ => Array.Empty<Parsing.Statements.Match>()
                                        }).Where((match) => match.Parts.First() is Parsing.Reference reference && reference.Refered == q))
                                       .SelectMany((q) => q);
                foreach (var match in recursiveMatches)
                {
                    hints.Add(new Validation.Hint
                    {
                        File = match.Diagnostics.File,
                        Line = match.Diagnostics.Line,
                        Message = $@"left recusion with top-level matches are not allowed in productions. Consider using left-recursive instead."
                    });
                }
                return hints;
            });
            // left-recursive has at least two matches
            validator.Register("XCG", ESeverity.Error, (parser) =>
            {
                var hints = new List<Validation.Hint>();
                foreach (var leftRecursive in parser.LeftRecursives)
                {
                    if (leftRecursive.Statements.Count < 2)
                    {
                        hints.Add(new Validation.Hint
                        {
                            File = leftRecursive.Diagnostics.File,
                            Line = leftRecursive.Diagnostics.Line,
                            Message = $@"left-recursive requires at least two matches."
                        });
                    }
                }
                return hints;
            });

            // left-recursive has exactly one alternative
            validator.Register("XCG", ESeverity.Error, (parser) =>
            {
                var hints = new List<Validation.Hint>();
                foreach (var leftRecursive in parser.LeftRecursives)
                {
                    if (leftRecursive.Statements.Count < 2)
                    {
                        hints.Add(new Validation.Hint
                        {
                            File = leftRecursive.Diagnostics.File,
                            Line = leftRecursive.Diagnostics.Line,
                            Message = $@"left-recursive requires at least two matches."
                        });
                    }
                }
                return hints;
            });
            // left-recursive matches (but last) start with the containing left-recursive
            validator.Register("XCG", ESeverity.Error, (parser) =>
            {
                var hints = new List<Validation.Hint>();
                foreach (var leftRecursive in parser.LeftRecursives.Where((q) => q.Statements.Count >= 2))
                {
                    var matches = leftRecursive.Statements.Where((q) => q is Parsing.Statements.Match).Cast<Parsing.Statements.Match>();
                    var count = matches.Count();
                    foreach (var match in matches.Take(count - 1))
                    {
                        if (match.Parts.First() is Parsing.Reference reference)
                        {
                            if (reference.Refered != leftRecursive)
                            {
                                hints.Add(new Validation.Hint
                                {
                                    File = leftRecursive.Diagnostics.File,
                                    Line = leftRecursive.Diagnostics.Line,
                                    Message = $@"Match must start with containing left-recursive."
                                });
                            }
                        }
                        else
                        {
                            throw new FatalException();
                        }
                    }
                }
                return hints;
            });
            // left-recursive last match refers to anything but the containing left-recursive
            validator.Register("XCG", ESeverity.Error, (parser) =>
            {
                var hints = new List<Validation.Hint>();
                foreach (var leftRecursive in parser.LeftRecursives.Where((q) => q.Statements.Count >= 2))
                {
                    var match = leftRecursive.Statements.Where((q) => q is Parsing.Statements.Match).Cast<Parsing.Statements.Match>().Last();
                    if (match.Parts.Last() is Parsing.Reference reference)
                    {
                        if (reference.Refered == leftRecursive)
                        {
                            hints.Add(new Validation.Hint
                            {
                                File = leftRecursive.Diagnostics.File,
                                Line = leftRecursive.Diagnostics.Line,
                                Message = $@"Last match of left-recursive must refer to anything but the left-recursive."
                            });
                        }
                    }
                    else
                    {
                        throw new FatalException();
                    }
                }
                return hints;
            });
            // left-recursive last match has exactly one part
            validator.Register("XCG", ESeverity.Error, (parser) =>
            {
                var hints = new List<Validation.Hint>();
                foreach (var leftRecursive in parser.LeftRecursives.Where((q) => q.Statements.Count >= 2))
                {
                    var match = leftRecursive.Statements.Where((q) => q is Parsing.Statements.Match).Cast<Parsing.Statements.Match>().Last();
                    if (match.Parts.Count != 1)
                    {
                        hints.Add(new Validation.Hint
                        {
                            File = leftRecursive.Diagnostics.File,
                            Line = leftRecursive.Diagnostics.Line,
                            Message = $@"Last match of left-recursive must have exactly one part."
                        });
                    }
                }
                return hints;
            });

            // require only ever refers to tokens
            validator.Register("XCG", ESeverity.Error, (parser) =>
            {
                var hints = new List<Validation.Hint>();
                var requires = parser.Tokens.SelectMany((q) => q.Statements.WhereIs<Parsing.TokenStatements.Require>());
                foreach (var require in requires)
                {
                    var references = require.Parts.WhereIs<Parsing.Reference>();
                    foreach (var reference in references)
                    {
                        if (reference.Refered is not Parsing.Token)
                        {
                            hints.Add(new Validation.Hint
                            {
                                Message = $@"Require may only refer to tokens."
                            });
                        }
                    }
                }
                return hints;
            });
        }
    }
}
