using System;

namespace XCG
{
    class Program
    {
        static void Main(string[] args)
        {
            var parser = new Parsing.Parser();
            foreach (var s in args)
            {
                if (System.IO.File.Exists(s))
                {
                    var contents = System.IO.File.ReadAllText(s);
                    if (parser.Parse(contents, out var parseNotes))
                    {
                        Console.ForegroundColor = ConsoleColor.Green;
                        Console.Error.WriteLine($"Parsing suceeded.");
                        Console.ResetColor();
                    }
                    else
                    {
                        Console.ForegroundColor = ConsoleColor.Red;
                        Console.Error.WriteLine($"Parsing failed.");
                        Console.ResetColor();
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
                    Console.Error.WriteLine($"File not found: {s}");
                    Console.ResetColor();
                }
            }
        }
    }
}
