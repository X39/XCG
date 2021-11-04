﻿using CommandLine;
using System;
using System.Collections.Generic;
using System.Linq;
using JetBrains.Annotations;

namespace XCG
{
    internal static class Program
    {
        [UsedImplicitly(ImplicitUseKindFlags.InstantiatedNoFixedConstructorSignature | ImplicitUseKindFlags.Assign)]
        private class CliOptions
        {
            [Option('i', "input", Required = true, HelpText = "Declares a single input xcg file.",
                MetaValue = "PATH ...")]
            public IEnumerable<string>? Input { get; [UsedImplicitly] set; }

            [Option('g', "generator", Required = true,
                HelpText = "Sets the generator to use. Might be a path to a file or one of the build-in ones.",
                MetaValue = "GENERATOR")]
            public string? Generator { get; [UsedImplicitly] set; }

            [Option('o', "output",
                HelpText = "Set the output filepath to where the generated file(s) should be generated to.",
                MetaValue = "PATH", Default = "output")]
            public string? Output { get; [UsedImplicitly] set; }

            [Option('s', "set", HelpText = "Allows to change generator-dependant settings.",
                MetaValue = "OPTION:VALUE ...")]
            public IEnumerable<string>? Settings { get; [UsedImplicitly] set; }

            [Option("options", HelpText = "Lists all options of a given generator.")]
            public bool ListOptions { get; [UsedImplicitly] set; }

            [Option('d', "dry-run", HelpText = "Will not generate any output files if set.")]
            public bool DryRun { get; [UsedImplicitly] set; }
        }

        private static void Colored(ESeverity severity, Action action)
        {
            Console.ForegroundColor = severity switch
            {
                ESeverity.Error => ConsoleColor.Red,
                ESeverity.Warning => ConsoleColor.Yellow,
                _ => Console.ForegroundColor
            };

            action();
            Console.ResetColor();
        }

        private static string SeverityString(ESeverity severity)
        {
            return severity switch
            {
                ESeverity.Error => "ERR",
                ESeverity.Warning => "WRN",
                ESeverity.Info => "INF",
                _ => string.Empty
            };
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
                ';' => "semicolon",
                '#' => "hash",
                '°' => "degree",
                '<' => "less-then",
                '>' => "greater-then",
                '(' => "round-bracket-open",
                ')' => "round-bracket-close",
                '[' => "square-bracket-open",
                ']' => "square-bracket-close",
                '{' => "curly-bracket-open",
                '}' => "curly-bracket-close",
                _ => null,
            };
        }

        private static IEnumerable<string> ResolveWildcards(IEnumerable<string> strings)
        {
            foreach (var filePathWithPossibleWildcard in strings)
            {
                if (filePathWithPossibleWildcard.Contains('*'))
                {
                    var splatted = filePathWithPossibleWildcard.Split('*');
                    var root = splatted.First();
                    var rootDir = System.IO.Path.GetDirectoryName(root);
                    if (rootDir is null)
                        throw new FatalException(
                            "Failed to apply wildcard - System.IO.Path.GetDirectoryName returned NULL.");
                    var files = System.IO.Directory.GetFiles(rootDir);
                    foreach (var filePath in files.Where((q) => q.StartsWith(root)))
                    {
                        var part = filePath[root.Length..];
                        var aborted = false;
                        foreach (var s in splatted.Skip(1).Where((q) => !string.IsNullOrWhiteSpace(q)))
                        {
                            var index = part.IndexOf(s, StringComparison.Ordinal);
                            if (index != -1)
                            {
                                part = part[(index + s.Length)..];
                            }
                            else
                            {
                                aborted = true;
                                break;
                            }
                        }

                        if (!aborted)
                        {
                            yield return filePath;
                        }
                    }
                }
                else
                {
                    yield return filePathWithPossibleWildcard;
                }
            }
        }

        private static int Main(string[] args)
        {
            CliOptions? cliOptions = null;
            var cliResult = Parser.Default.ParseArguments<CliOptions>(args)
                .WithParsed((options) => cliOptions = options);
            if (cliResult.Tag == ParserResultType.NotParsed || cliOptions is null)
            {
                return -1;
            }

            #region Parsing

            var parser = new Parsing.Parser();
            var parseOk = true;
            foreach (var s in ResolveWildcards(cliOptions.Input ?? Array.Empty<string>()))
            {
                var filePath = System.IO.Path.GetFullPath(s);
                if (System.IO.File.Exists(filePath))
                {
                    var contents = System.IO.File.ReadAllText(s);
                    var parseResult = parser.Parse(filePath, contents, out var parseNotes);
                    foreach (var it in parseNotes)
                    {
                        Colored(it.Severity, () => Console.WriteLine(it.Message));
                    }

                    if (parseResult)
                    {
                        Console.BackgroundColor = ConsoleColor.Green;
                        Console.ForegroundColor = ConsoleColor.Black;
                        Console.WriteLine($"Parsing {filePath} ({s}) succeeded.");
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

            var generatedReferences = 0;
            var endOfLineToken = new Parsing.Token
            {
                Identifier = "@eol",
                Children = new List<Parsing.ITokenStatement>
                {
                    new Parsing.TokenStatements.Require
                    {
                        Negated = false,
                        Range = new Parsing.Multiplicity(1,
                            new Parsing.Diagnostic {Column = 0, File = "---auto-generated---", Line = 0, Offset = 0}),
                        Parts = new List<Parsing.IStatement>
                        {
                            new Parsing.Word("\n")
                        }
                    }
                }
            };
            var endOfFileToken = new Parsing.Token
            {
                Identifier = "@eof",
                Children = new List<Parsing.ITokenStatement>
                {
                    new Parsing.TokenStatements.Require
                    {
                        Negated = false,
                        Range = new Parsing.Multiplicity(1,
                            new Parsing.Diagnostic {Column = 0, File = "---auto-generated---", Line = 0, Offset = 0}),
                        Parts = new List<Parsing.IStatement>
                        {
                            new Parsing.Word("\0")
                        }
                    }
                }
            };
            foreach (var reference in parser.References)
            {
                generatedReferences++;
                reference.CaptureName ??= $"capture{generatedReferences}";
                Parsing.IStatement? possibleActual;

                if (reference.IsAlias)
                {
                    possibleActual = parser.Tokens.FirstOrDefault((q) => q.Alias == reference.Text);
                    if (possibleActual is not null)
                    {
                        reference.Refered = possibleActual;
                        continue;
                    }
                }
                else
                {
                    if (reference.Text.Equals("eol", StringComparison.InvariantCultureIgnoreCase))
                    {
                        reference.Refered = endOfLineToken;
                        if (!parser.Tokens.Contains(endOfLineToken))
                        {
                            parser.Tokens.Add(endOfLineToken);
                        }

                        continue;
                    }

                    if (reference.Text.Equals("eof", StringComparison.InvariantCultureIgnoreCase))
                    {
                        reference.Refered = endOfFileToken;
                        if (!parser.Tokens.Contains(endOfFileToken))
                        {
                            parser.Tokens.Add(endOfFileToken);
                        }

                        continue;
                    }

                    possibleActual = parser.Tokens.FirstOrDefault((q) => q.Identifier == reference.Text);
                    if (possibleActual is not null)
                    {
                        reference.Refered = possibleActual;
                        continue;
                    }

                    possibleActual = parser.Productions.FirstOrDefault((q) => q.Identifier == reference.Text);
                    if (possibleActual is not null)
                    {
                        reference.Refered = possibleActual;
                        continue;
                    }

                    possibleActual = parser.LeftRecursiveItems.FirstOrDefault((q) => q.Identifier == reference.Text);
                    if (possibleActual is not null)
                    {
                        reference.Refered = possibleActual;
                        continue;
                    }

                    possibleActual = parser.Messages.FirstOrDefault((q) => q.Identifier == reference.Text);
                    if (possibleActual is not null)
                    {
                        reference.Refered = possibleActual;
                        continue;
                    }
                }

                if (!reference.IsAlias) continue;
                string identifier;
                if (reference.Text.All((c) => ToStringRepresentation(c) != null))
                {
                    identifier = string.Concat("@",
                        string.Join("-", reference.Text.Select(ToStringRepresentation)));
                }
                else if (reference.Text.All((c) => char.IsLetterOrDigit(c) || c == '-'))
                {
                    identifier = string.Concat("@", reference.Text.ToLower());
                }
                else
                {
                    identifier = $"@auto-{generatedReferences}";
                }

                var token = new Parsing.Token
                {
                    Alias = reference.Text,
                    Identifier = identifier,
                    Children = new List<Parsing.ITokenStatement>
                    {
                        new Parsing.TokenStatements.Require
                        {
                            Negated = false,
                            Range = new Parsing.Multiplicity(1,
                                new Parsing.Diagnostic
                                    {Column = 0, File = "---auto-generated---", Line = 0, Offset = 0}),
                            Parts = new List<Parsing.IStatement>
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
            IGenerator? generator;
            switch (cliOptions.Generator?.ToLower())
            {
                case "cpp":
                case "c++":
                    generator = new Generators.Cpp.CppGenerator();
                    break;
                case null: return -1;
                default:
                    var generatorAbsolute = System.IO.Path.GetFullPath(cliOptions.Generator);
                    if (System.IO.File.Exists(generatorAbsolute))
                    {
                        try
                        {
                            var reflectionOnlyAssembly =
                                System.Reflection.Assembly.ReflectionOnlyLoadFrom(generatorAbsolute);
                            if (reflectionOnlyAssembly.GetExportedTypes()
                                .Any((t) => t.IsAssignableTo(typeof(IGenerator))))
                            {
                                var assembly = System.Reflection.Assembly.Load(generatorAbsolute);
                                var generatorType = assembly.GetExportedTypes()
                                    .First((t) => t.IsAssignableFrom(typeof(IGenerator)));
                                try
                                {
                                    generator = (IGenerator) Activator.CreateInstance(generatorType)!;
                                }
                                catch (Exception ex)
                                {
                                    Console.BackgroundColor = ConsoleColor.Red;
                                    Console.ForegroundColor = ConsoleColor.White;
                                    Console.WriteLine(
                                        $"Failed to create instance of IGenerator with {generatorAbsolute} ({cliOptions.Generator}):");
                                    Console.WriteLine(ex.Message);
                                    Console.ResetColor();
                                    return -1;
                                }
                            }
                            else
                            {
                                Console.BackgroundColor = ConsoleColor.Red;
                                Console.ForegroundColor = ConsoleColor.White;
                                Console.WriteLine(
                                    $"Assembly {generatorAbsolute} ({cliOptions.Generator}) is not containing a usable IGenerator implementation.");
                                Console.ResetColor();
                                return -1;
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
                        return -1;
                    }

                    break;
            }

            #endregion

            #region List Generator Options

            if (cliOptions.ListOptions)
            {
                foreach (var it in generator.GetOptions())
                {
                    Console.WriteLine($"{it.option}:{it.value}");
                }
            }

            #endregion

            #region Set Generator Options

            // Set generator options
            var optionError = false;
            foreach (var option in cliOptions.Settings ?? Array.Empty<string>())
            {
                string key;
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
                    Console.Error.WriteLine(string.Concat(ex.GetType().Name, ": ", ex.Message));
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
                () => Console.WriteLine(
                    $"[{rule.Realm}{rule.Code:000}][{SeverityString(rule.Severity)}][{hint.File}][L{hint.Line}]: {hint.Message}"))))
            {
                return -1;
            }

            #endregion

            if (cliOptions.DryRun)
            {
                return 0;
            }

            // Tell the generator to generate the parser
            var outputPath = System.IO.Path.GetFullPath(cliOptions.Output ?? Environment.CurrentDirectory);
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
                Console.WriteLine(
                    "or raise an issue (or comment under some existing with your pattern) at https://github.com/X39/XCG.");
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
                    .Concat(parser.LeftRecursiveItems.Select((q) => q.Identifier))
                    .Concat(parser.Messages.Select((q) => q.Identifier))
                    .GroupBy((q) => q)
                    .Where((q) => q.Count() > 1)
                    .Select((q) => q.Key)
                    .ToHashSet();
                foreach (var tuple in parser.Tokens.Select((q) => (diag: q.Diagnostics, ident: q.Identifier))
                    .Concat(parser.Productions.Select((q) => (diag: q.Diagnostics, ident: q.Identifier)))
                    .Concat(parser.LeftRecursiveItems.Select((q) => (diag: q.Diagnostics, ident: q.Identifier)))
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
            // All references have referred
            validator.Register("XCG", ESeverity.Error, (parser) =>
            {
                return parser.Productions.Concat<Parsing.IStatement>(parser.LeftRecursiveItems)
                    .SelectMany((reference) => reference.FindChildren<Parsing.Reference>())
                    .Where((reference) => reference.Refered is null)
                    .Select((reference) => new Validation.Hint
                    {
                        File = reference.Diagnostics.File,
                        Line = reference.Diagnostics.Line,
                        Message = $@"Reference {{ {reference.Text} }} is not referring to anything existing."
                    });
            });
            // Alias Collision
            validator.Register("XCG", ESeverity.Warning, (parser) =>
            {
                var hints = new List<Validation.Hint>();
                var identifiers = parser.Tokens.Select((q) => q.Identifier)
                    .Concat(parser.Tokens.Select((q) => q.Alias).Where((q) => !string.IsNullOrWhiteSpace(q)))
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
            // Left-recursion in production at top level
            validator.Register("XCG", ESeverity.Error, (parser) =>
            {
                var hints = new List<Validation.Hint>();
                var recursiveMatches = (from q in parser.Productions
                        where q.Children.Any()
                        select (q.Children.First() switch
                        {
                            Parsing.Statements.Alternatives alternatives => alternatives.Matches
                                .Where((q2) => q2.Matches.First() is Parsing.Reference),
                            Parsing.Statements.Match match => match.Matches.First() is Parsing.Reference reference
                                                              && reference.Refered == q
                                ? new[] {match}
                                : Array.Empty<Parsing.Statements.Match>(),
                            _ => Array.Empty<Parsing.Statements.Match>()
                        }).Where((match) =>
                            match.Matches.First() is Parsing.Reference reference && reference.Refered == q))
                    .SelectMany((q) => q);
                foreach (var match in recursiveMatches)
                {
                    hints.Add(new Validation.Hint
                    {
                        File = match.Diagnostics.File,
                        Line = match.Diagnostics.Line,
                        Message =
                            $@"left recursion with top-level matches are not allowed in productions. Consider using left-recursive instead."
                    });
                }

                return hints;
            });
            // left-recursive has at least two matches
            validator.Register("XCG", ESeverity.Error, (parser) =>
            {
                var hints = new List<Validation.Hint>();
                foreach (var leftRecursive in parser.LeftRecursiveItems)
                {
                    if (leftRecursive.Children.Count < 2)
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
                foreach (var leftRecursive in parser.LeftRecursiveItems)
                {
                    if (leftRecursive.Children.Count < 2)
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
                foreach (var leftRecursive in parser.LeftRecursiveItems.Where((q) => q.Children.Count >= 2))
                {
                    var matches = leftRecursive.Children
                        .Where((q) => q is Parsing.Statements.Match)
                        .Cast<Parsing.Statements.Match>()
                        .ToArray();
                    var count = matches.Count();
                    foreach (var match in matches.Take(count - 1))
                    {
                        if (match.Matches.First() is Parsing.Reference reference)
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
                foreach (var leftRecursive in parser.LeftRecursiveItems.Where((q) => q.Children.Count >= 2))
                {
                    var match = leftRecursive.Children.Where((q) => q is Parsing.Statements.Match)
                        .Cast<Parsing.Statements.Match>().Last();
                    if (match.Matches.Last() is Parsing.Reference reference)
                    {
                        if (reference.Refered == leftRecursive)
                        {
                            hints.Add(new Validation.Hint
                            {
                                File = leftRecursive.Diagnostics.File,
                                Line = leftRecursive.Diagnostics.Line,
                                Message =
                                    $@"Last match of left-recursive must refer to anything but the left-recursive."
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
                foreach (var leftRecursive in parser.LeftRecursiveItems.Where((q) => q.Children.Count >= 2))
                {
                    var match = leftRecursive.Children.Where((q) => q is Parsing.Statements.Match)
                        .Cast<Parsing.Statements.Match>().Last();
                    if (match.Matches.Count != 1)
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

            // require references must refer to anything
            validator.Register("XCG", ESeverity.Error, (parser) =>
            {
                var hints = new List<Validation.Hint>();
                var requires = parser.Tokens.SelectMany((q) => q.Children.WhereIs<Parsing.TokenStatements.Require>());
                foreach (var require in requires)
                {
                    var references = require.Parts.WhereIs<Parsing.Reference>();
                    foreach (var reference in references)
                    {
                        if (reference.Refered is null)
                        {
                            hints.Add(new Validation.Hint
                            {
                                Line = require.Diagnostics.Line,
                                File = require.Diagnostics.File,
                                Message = $@"Reference {{ {reference.Text} }} is not referring to anything."
                            });
                        }
                    }
                }

                return hints;
            });

            // backtrack references must refer to to tokens
            validator.Register("XCG", ESeverity.Error, (parser) =>
            {
                var hints = new List<Validation.Hint>();
                var requires = parser.Tokens.SelectMany((q) => q.Children.WhereIs<Parsing.TokenStatements.Require>());
                foreach (var require in requires)
                {
                    var references = require.Parts.WhereIs<Parsing.Reference>();
                    foreach (var reference in references)
                    {
                        if (reference.Refered is not null && reference.Refered is not Parsing.Token)
                        {
                            hints.Add(new Validation.Hint
                            {
                                Line = require.Diagnostics.Line,
                                File = require.Diagnostics.File,
                                Message =
                                    $@"Reference {{ {reference.Text} }} may only refer to tokens but refers to a {reference.Refered.GetType().FullName}."
                            });
                        }
                    }
                }

                return hints;
            });

            // require references must refer to to tokens
            validator.Register("XCG", ESeverity.Error, (parser) =>
            {
                var hints = new List<Validation.Hint>();
                var backtracks =
                    parser.Tokens.SelectMany((q) => q.Children.WhereIs<Parsing.TokenStatements.Backtrack>());
                foreach (var backtrack in backtracks)
                {
                    var references = backtrack.Parts.WhereIs<Parsing.Reference>();
                    foreach (var reference in references)
                    {
                        if (reference.Refered is not null && reference.Refered is not Parsing.Token)
                        {
                            hints.Add(new Validation.Hint
                            {
                                Line = backtrack.Diagnostics.Line,
                                File = backtrack.Diagnostics.File,
                                Message =
                                    $@"Reference {{ {reference.Text} }} may only refer to tokens but refers to a {reference.Refered.GetType().FullName}."
                            });
                        }
                    }
                }

                return hints;
            });
            // alternatives with error is always direct child of while
            validator.Register("XCG", ESeverity.Error, (parser) =>
            {
                var hints = new List<Validation.Hint>();
                foreach (var result in parser.Productions.Select(production =>
                    production.FindChildrenWithParents<Parsing.Statements.Alternatives>()))
                {
                    foreach (var (alternatives, parents) in result)
                    {
                        if (alternatives.CatchesErrors && parents.First() is not Parsing.Statements.While)
                        {
                            hints.Add(new Validation.Hint
                            {
                                Line = alternatives.Diagnostics.Line,
                                File = alternatives.Diagnostics.File,
                                Message = $@"Alternatives with error may only occur inside of a while."
                            });
                        }
                    }
                }

                return hints;
            });
            // while with alternatives having error may only have that single alternatives entry
            validator.Register("XCG", ESeverity.Error, (parser) =>
            {
                var hints = new List<Validation.Hint>();
                foreach (var production in parser.Productions)
                {
                    var result = production.FindChildrenWithParents<Parsing.Statements.Alternatives>();

                    foreach (var (alternatives, parents) in result)
                    {
                        if (alternatives.CatchesErrors && parents.First() is Parsing.Statements.While @while &&
                            @while.Children.Count != 1)
                        {
                            hints.Add(new Validation.Hint
                            {
                                Line = @while.Diagnostics.Line,
                                File = @while.Diagnostics.File,
                                Message =
                                    $@"A while containing alternatives catching errors may not contain anything but that alternatives."
                            });
                        }
                    }
                }

                return hints;
            });
            // find unused productions
            validator.Register("XCG", ESeverity.Warning, (parser) =>
            {
                var mainProduction = parser.Productions.FirstOrDefault((q) => q.Identifier == "main");
                if (mainProduction is null)
                {
                    return Array.Empty<Validation.Hint>();
                }

                var productionDictionary = parser.Productions.ToDictionary((q) => q, (_) => 0);
                productionDictionary[mainProduction]++;
                var visited = new HashSet<Parsing.IStatement>();

                void Walk(Parsing.IStatement statement)
                {
                    if (visited.Contains(statement))
                    {
                        return;
                    }

                    visited.Add(statement);
                    var references = statement.FindChildren<Parsing.Reference>();
                    foreach (var reference in references)
                    {
                        if (reference.Refered is Parsing.Production production)
                        {
                            productionDictionary[production]++;
                        }

                        if (reference.Refered is { } childStatement)
                        {
                            Walk(childStatement);
                        }
                    }
                }

                Walk(mainProduction);

                return productionDictionary.Where((kvp) => kvp.Value == 0)
                    .Where((kvp) => kvp.Key.Identifier.ToLower() != "main").Select((kvp) => new Validation.Hint
                    {
                        Line = kvp.Key.Diagnostics.Line,
                        File = kvp.Key.Diagnostics.File,
                        Message = $@"Production {kvp.Key.Identifier} is unused."
                    });
            });
            // find unused left-recursive
            validator.Register("XCG", ESeverity.Warning, (parser) =>
            {
                var mainProduction = parser.Productions.FirstOrDefault((q) => q.Identifier == "main");
                if (mainProduction is null)
                {
                    return Array.Empty<Validation.Hint>();
                }

                var leftRecursiveDictionary = parser.LeftRecursiveItems.ToDictionary((q) => q, (_) => 0);
                var visited = new HashSet<Parsing.IStatement>();

                void Walk(Parsing.IStatement statement)
                {
                    if (visited.Contains(statement))
                    {
                        return;
                    }

                    visited.Add(statement);
                    var references = statement.FindChildren<Parsing.Reference>();
                    foreach (var reference in references)
                    {
                        if (reference.Refered is Parsing.LeftRecursive leftRecursive)
                        {
                            leftRecursiveDictionary[leftRecursive]++;
                        }

                        if (reference.Refered is { } childStatement)
                        {
                            Walk(childStatement);
                        }
                    }
                }

                Walk(mainProduction);

                return leftRecursiveDictionary.Where((kvp) => kvp.Value == 0)
                    .Where((kvp) => kvp.Key.Identifier.ToLower() != "main").Select((kvp) => new Validation.Hint
                    {
                        Line = kvp.Key.Diagnostics.Line,
                        File = kvp.Key.Diagnostics.File,
                        Message = $@"Left-Recursive {kvp.Key.Identifier} is unused."
                    });
            });

            // references with print instructions only ever have message as referred
            validator.Register("XCG", ESeverity.Error, (parser) =>
            {
                var hints = new List<Validation.Hint>();
                foreach (var result in parser.Productions.Select(production =>
                    production.FindChildren<Parsing.Statements.Print>()))
                {
                    hints.AddRange(from print in result
                        where print.Reference.Refered is not Parsing.Message
                        select new Validation.Hint
                        {
                            Line = print.Diagnostics.Line, File = print.Diagnostics.File,
                            Message = $@"The print instruction must always refer to a message."
                        });
                }

                return hints;
            });
            // ensure all comments have start
            validator.Register("XCG", ESeverity.Error, (parser) =>
            {
                return parser.Comments.Where((comment) => comment.Start is null).Select((comment) => new Validation.Hint
                {
                    Line = comment.Diagnostics.Line,
                    File = comment.Diagnostics.File,
                    Message = $@"Comment is lacking start."
                });
            });
            // ensure all comments have end
            validator.Register("XCG", ESeverity.Error, (parser) =>
            {
                return parser.Comments.Where((comment) => comment.End is null).Select((comment) => new Validation.Hint
                {
                    Line = comment.Diagnostics.Line,
                    File = comment.Diagnostics.File,
                    Message = $@"Comment is lacking end."
                });
            });
            // ensure all productions are non-empty
            validator.Register("XCG", ESeverity.Error, (parser) =>
            {
                return parser.Productions
                    .Where((production) => production.Children.All(
                        (q) => q is Parsing.Statements.While
                            or Parsing.Statements.If
                            or Parsing.Statements.Set
                            or Parsing.Statements.Get
                            or Parsing.Statements.Print))
                    .Where((production) =>
                        !production.Identifier.Equals("main", StringComparison.InvariantCultureIgnoreCase))
                    .Select((production) => new Validation.Hint
                    {
                        Line = production.Diagnostics.Line,
                        File = production.Diagnostics.File,
                        Message = $@"Possibly empty productions are not allowed."
                    });
            });
        }
    }
}