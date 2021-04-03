using System;

namespace XCG
{
    class Program
    {
        static int Main(string[] args)
        {
            var parser = new Parsing.Parser();
            bool parseOk = true;
            foreach (var s in args)
            {
                var filePath = System.IO.Path.GetFullPath(s);
                if (System.IO.File.Exists(filePath))
                {
                    var contents = System.IO.File.ReadAllText(s);
                    var parseResult = parser.Parse(contents, out var parseNotes);
                    foreach (var it in parseNotes)
                    {
                        switch (it.Severity)
                        {
                            case Parsing.ESeverity.Error:
                                Console.ForegroundColor = ConsoleColor.Red;
                                break;
                            case Parsing.ESeverity.Warning:
                                Console.ForegroundColor = ConsoleColor.Yellow;
                                break;
                        }
                        Console.WriteLine(it.Message);
                        Console.ResetColor();
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
                    foreach (var it in parseNotes)
                    {
                        switch (it.Severity)
                        {
                            case Parsing.ESeverity.Error:
                                Console.ForegroundColor = ConsoleColor.Red;
                                break;
                            case Parsing.ESeverity.Warning:
                                Console.ForegroundColor = ConsoleColor.Yellow;
                                break;
                        }
                        Console.WriteLine(it.Message);
                        Console.ResetColor();
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
            return 0;
        }
    }
}
