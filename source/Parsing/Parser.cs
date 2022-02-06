using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using JetBrains.Annotations;

namespace XCG.Parsing;

public class Parser
{
    #region State

    private bool _isParsing;
    private int _index = -1;
    private int _line = 1;
    private int _column = 1;
    private string _contents = string.Empty;
    private List<ParseNote> _parseNotes = new();
    private string? _file;

    #endregion

    public List<Token> Tokens { get; } = new();
    public List<Reference> References { get; } = new();
    public List<Statements.Set> Setters { get; } = new();
    public List<Message> Messages { get; } = new();
    public List<Production> Productions { get; } = new();
    public List<LeftRecursive> LeftRecursiveItems { get; } = new();
    public List<Comment> Comments { get; } = new();


    private string Formatted(string msg)
    {
        return $"[L{_line}|C{_column}] {msg.Replace("\r", "")}";
    }

    [PublicAPI]
    private ParseNote Inf(string msg)
    {
        return new ParseNote
        {
            Message = Formatted(msg),
            Severity = ESeverity.Info
        };
    }

    [PublicAPI]
    private ParseNote Wrn(string msg)
    {
        return new ParseNote
        {
            Message = Formatted(msg),
            Severity = ESeverity.Warning
        };
    }

    [PublicAPI]
    private ParseNote Err(string msg)
    {
        return new ParseNote
        {
            Message = Formatted(msg),
            Severity = ESeverity.Error
        };
    }

    /// <summary>
    /// Attempts to match the given <paramref name="expected"/>, ensuring that
    /// the following character is a whitespace character.
    /// </summary>
    /// <param name="expected">The keyword to check for</param>
    /// <param name="ignoreCase">whether to ignore casing or not</param>
    /// <param name="skipWs">whether to skip any possible initial whitespace</param>
    /// <returns>True if keyword was matched, false if not</returns>
    private bool TryMatchNoCapture(string expected, bool ignoreCase = true, bool skipWs = true)
    {
        var localIndex = _index;
        var stringComparison =
            ignoreCase ? StringComparison.InvariantCultureIgnoreCase : StringComparison.InvariantCulture;
        if (skipWs)
        {
            Skip(ref localIndex);
        }

        return _contents.Length - localIndex > expected.Length
               && (
                   _contents[localIndex..(localIndex + expected.Length)].Equals(expected, stringComparison)
                   && (
                       _contents.Length - localIndex + expected.Length <= 1
                       || char.IsWhiteSpace(_contents[localIndex + expected.Length])
                   )
               );
    }

    /// <summary>
    /// Peeks the offset of <paramref name="la"/> in correspondence to <see cref="_index"/> character from <see cref="_contents"/>
    /// </summary>
    /// <param name="localIndex"></param>
    /// <param name="la">Look-Ahead offset</param>
    /// <returns></returns>
    private char PeekChar(ref int localIndex, int la = 1)
    {
        la -= 1;
        return localIndex < 0
            ? (localIndex - la < 0 ? '\0' : _contents[localIndex - la])
            : (localIndex + la < _contents.Length ? _contents[localIndex + la] : '\0');
    }

    /// <summary>
    /// Peeks the offset of <paramref name="la"/> in correspondence to <see cref="_index"/> character from <see cref="_contents"/>
    /// </summary>
    /// <param name="la">Look-Ahead offset</param>
    /// <returns></returns>
    private char PeekChar(int la = 1) => PeekChar(ref _index, la);

    /// <summary>
    /// Consumes a single character from <see cref="_contents"/>.
    /// </summary>
    /// <remarks>
    /// Will progress <see cref="_index"/> on success.
    /// </remarks>
    /// <returns></returns>
    private char NextChar()
    {
        var c = PeekChar();
        switch (c)
        {
            case '\n':
                _line++;
                _column++;
                goto default;
            default:
                _index++;
                return c;
            case '\0':
                return '\0';
        }
    }

    /// <summary>
    /// Returns the current character in <see cref="_contents"/> according to <see cref="_index"/>
    /// </summary>
    /// <returns></returns>
    private char CurrentChar()
    {
        return PeekChar();
    }

    /// <summary>
    /// Attempts to match the given <paramref name="expected"/>, ensuring that
    /// the following character is a whitespace character.
    /// </summary>
    /// <remarks>
    /// Will progress <see cref="_index"/> on success.
    /// </remarks>
    /// <param name="expected">The keyword to check for</param>
    /// <param name="ignoreCase">whether to ignore casing or not</param>
    /// <returns>True if keyword was matched, false if not</returns>
    private bool TryMatch(string expected, bool ignoreCase = true)
    {
        var stringComparison =
            ignoreCase ? StringComparison.InvariantCultureIgnoreCase : StringComparison.InvariantCulture;
        if (_contents.Length - _index > expected.Length)
        {
            if (_contents[_index..(_index + expected.Length)].Equals(expected, stringComparison))
            {
                if (_contents.Length - _index + expected.Length > 1)
                {
                    if (char.IsWhiteSpace(_contents[_index + expected.Length]))
                    {
                        _index += expected.Length;
                        _column += expected.Length;
                        return true;
                    }

                    return false;
                }

                _index += expected.Length;
                _column += expected.Length;
                return true;
            }

            return false;
        }

        return false;
    }

    /// <summary>
    /// Checks and Skips the whitespace level (<paramref name="wsLevel"/>).
    /// </summary>
    /// <remarks>
    /// Will progress <see cref="_index"/> on success.
    /// </remarks>
    /// <param name="wsLevel">The amount of whitespaces</param>
    /// <param name="wsChars">The characters considered whitespace</param>
    /// <returns>True if whitespace level matches, false if not</returns>
    private bool SkipWhiteSpaceLevel(int wsLevel, string wsChars = " \t")
    {
        if (_index + wsLevel >= _contents.Length)
        {
            return false;
        }

        for (var i = _index; i < _index + wsLevel; i++)
        {
            if (!wsChars.Contains(_contents[i]))
            {
                return false;
            }
        }

        _index += wsLevel;
        _column += wsLevel;
        return true;
    }

    /// <summary>
    /// Skips until a character not in <paramref name="chars"/> is encountered.
    /// </summary>
    /// <param name="chars">The characters to skip</param>
    /// <param name="localIndex">Index to progress</param>
    private void Skip(ref int localIndex, string chars = " \t\r")
    {
        char la;
        var commentMode = false;
        while ((la = PeekChar(ref localIndex)) != '\0')
        {
            if (commentMode)
            {
                if (la == '*' && PeekChar(ref localIndex, 2) == '/')
                {
                    localIndex += 2;
                    commentMode = false;
                }
                else
                {
                    localIndex++;
                }
            }
            else if (la == '/' && PeekChar(ref localIndex, 2) == '*')
            {
                localIndex += 2;
                commentMode = true;
            }
            else if (chars.Contains(la))
            {
                localIndex++;
            }
            else
            {
                break;
            }
        }
    }

    /// <summary>
    /// Continues reading until end-of-line is hit
    /// </summary>
    /// <returns></returns>
    private string ReadToEndOfLine()
    {
        var startIndex = _index;
        char la;
        while ((la = PeekChar()) != '\n' && la != '\0')
        {
            NextChar();
        }

        var endIndex = _index;
        return _contents[startIndex..endIndex];
    }

    /// <summary>
    /// Skips until a character not in <paramref name="chars"/> is encountered.
    /// If next characters equal <code>/*</code>, comment mode is enabled until <code>*/</code> is encountered.
    /// </summary>
    /// <remarks>
    /// Will progress <see cref="_index"/>.
    /// </remarks>
    /// <param name="chars">The characters to skip</param>
    private void Skip(string chars = " \t\r")
    {
        char la;
        var commentMode = false;
        while ((la = PeekChar()) != '\0')
        {
            if (commentMode)
            {
                if (la == '*' && PeekChar(2) == '/')
                {
                    NextChar();
                    NextChar();
                    commentMode = false;
                }
                else
                {
                    NextChar();
                }
            }
            else if (la == '/' && PeekChar(2) == '*')
            {
                NextChar();
                NextChar();
                commentMode = true;
            }
            else if (chars.Contains(la))
            {
                NextChar();
            }
            else
            {
                break;
            }
        }
    }

    /// <summary>
    /// Skips until a character not in <paramref name="chars"/> is encountered.
    /// Will also consume a single newline and immediately stop afterwards
    /// </summary>
    /// <remarks>
    /// Will progress <see cref="_index"/>.
    /// </remarks>
    /// <param name="chars">The characters to skip</param>
    private void SkipLine(string chars = " \t\r")
    {
        Skip(chars);
        if (_index < _contents.Length && _contents[_index] == '\n')
        {
            _line++;
            _index++;
            _column = 1;
        }
    }

    /// <summary>
    /// Counts the whitespaces following from current <see cref="_index"/>.
    /// </summary>
    /// <param name="wsChars">The characters considered whitespace</param>
    /// <returns>The amount of whitespaces encountered.</returns>
    private int CountWhiteSpaces(string wsChars = " \t")
    {
        for (var i = _index; i < _contents.Length; i++)
        {
            if (!wsChars.Contains(_contents[i]))
            {
                return i - _index;
            }
        }

        return _contents.Length - _index;
    }

    /// <summary>
    /// Attempts to read in an identifier conforming to `[a-zA-Z][-_a-z0-0`A-Z]*`.
    /// </summary>
    /// <remarks>
    /// Will progress <see cref="_index"/> on success.
    /// </remarks>
    /// <param name="ident"></param>
    /// <returns>Returns true if an ident of >=1 is found</returns>
    private bool TryReadIdent(out string ident)
    {
        if (_index >= _contents.Length || !((_contents[_index] >= 'a' && _contents[_index] <= 'z') ||
                                            (_contents[_index] >= 'A' && _contents[_index] <= 'Z')))
        {
            ident = string.Empty;
            return false;
        }

        var startIndex = _index;
        _index++;
        _column++;
        while (_index < _contents.Length &&
               ((_contents[_index] >= 'a' && _contents[_index] <= 'z')
                || (_contents[_index] >= 'A' && _contents[_index] <= 'Z')
                || (_contents[_index] >= '0' && _contents[_index] <= '9')
                || _contents[_index] == '-'
                || _contents[_index] == '_'))
        {
            _index++;
            _column++;
        }

        ident = _contents.Substring(startIndex, _index - startIndex);
        return true;
    }

    /// <summary>
    /// Attempts to read in an quoted string, unescaping escaped
    /// quotes.
    /// </summary>
    /// <remarks>
    /// Will progress <see cref="_index"/> on success.
    /// </remarks>
    /// <param name="quotedString"></param>
    /// <returns>Returns true if string is found and it is terminated.</returns>
    private bool TryReadQuotedString(out string quotedString)
    {
        if (_index >= _contents.Length || _contents[_index] != '"')
        {
            quotedString = string.Empty;
            return false;
        }

        var localIndex = _index;
        localIndex++;
        var col = _column;
        var lin = _line;
        col++;
        var builder = new StringBuilder();
        while (localIndex < _contents.Length)
        {
            if (_contents[localIndex] == '"')
            {
                if (localIndex + 1 < _contents.Length && _contents[localIndex + 1] == '"')
                {
                    localIndex++;
                }
                else
                {
                    break;
                }
            }
            else if (_contents[localIndex] == '\n')
            {
                col = 0;
                lin++;
            }

            builder.Append(_contents[localIndex]);
            localIndex++;
            col++;
        }

        if (localIndex < _contents.Length && _contents[localIndex] == '"')
        {
            localIndex++;
            col++;
            _index = localIndex;
            _column = col;
            _line = lin;
            quotedString = builder.ToString();
            return true;
        }

        quotedString = string.Empty;
        return false;
    }

    /// <summary>
    /// Reads in a whole <see cref="Message"/>.
    /// </summary>
    /// <param name="wsLevel">The level of whitespace this is expected to start at.</param>
    /// <returns>Either a valid token or null if something moved wrong</returns>
    private Message? ParseMessage(int wsLevel)
    {
        if (!SkipWhiteSpaceLevel(wsLevel) || !TryMatch("message"))
        {
            _parseNotes.Add(Err("Failed to read token"));
            return null;
        }

        var message = new Message {Diagnostics = GetDiagnostic()};
        Skip();
        if (!TryReadIdent(out var ident))
        {
            _parseNotes.Add(Err("Missing ident"));
        }

        message.Identifier = ident;

        SkipLine();
        int newWsLevel;
        while ((newWsLevel = CountWhiteSpaces()) > wsLevel)
        {
            SkipWhiteSpaceLevel(newWsLevel);
            if (TryMatchNoCapture(""))
            {
            }
            else if (TryMatch("with"))
            {
                var res = ReadToEndOfLine();
                message.Text = res.Trim();
            }
            else if (TryMatch("level"))
            {
                var res = ReadToEndOfLine().Trim();
                message.Severity = res.ToLower() switch
                {
                    "error" => ESeverity.Error,
                    "info" => ESeverity.Info,
                    "warning" => ESeverity.Warning,
                    _ => ((Func<ESeverity>) (() =>
                    {
                        _parseNotes.Add(Wrn($@"Unknown level '{res}', defaulting to error."));
                        return ESeverity.Error;
                    }))()
                };
            }
            else
            {
                var readTilEndOfLine = ReadToEndOfLine();
                _parseNotes.Add(Err($"Unknown instruction `{readTilEndOfLine}`"));
            }

            SkipLine();
        }

        if (string.IsNullOrWhiteSpace(message.Text))
        {
            _parseNotes.Add(Wrn("Message has empty text."));
        }

        return message;
    }

    /// <summary>
    /// Reads in a whole <see cref="Production"/>.
    /// </summary>
    /// <param name="wsLevel">The level of whitespace this is expected to start at.</param>
    /// <returns>Either a valid token or null if something moved wrong</returns>
    private Production? ParseProduction(int wsLevel)
    {
        if (!SkipWhiteSpaceLevel(wsLevel) || !TryMatch("production"))
        {
            _parseNotes.Add(Err("Failed to read production"));
            return null;
        }

        var production = new Production {Diagnostics = GetDiagnostic()};
        Skip();
        if (!TryReadIdent(out var ident))
        {
            _parseNotes.Add(Err("Missing ident"));
        }

        production.Identifier = ident;

        SkipLine();
        int newWsLevel;
        while ((newWsLevel = CountWhiteSpaces()) > wsLevel)
        {
            var subStatement = ParseStatement(newWsLevel);
            if (subStatement != null)
            {
                production.Children.Add(subStatement);
            }

            if (PeekChar(0) != '\n')
            {
                SkipLine();
            }
        }

        return production;
    }

    private LeftRecursive? ParseLeftRecursive(int wsLevel)
    {
        if (!SkipWhiteSpaceLevel(wsLevel) || !TryMatch("left-recursive"))
        {
            _parseNotes.Add(Err("Failed to read left-recursive"));
            return null;
        }

        var leftRecursive = new LeftRecursive {Diagnostics = GetDiagnostic()};
        Skip();
        if (!TryReadIdent(out var ident))
        {
            _parseNotes.Add(Err("Missing ident"));
        }

        leftRecursive.Identifier = ident;

        SkipLine();
        int newWsLevel;
        while ((newWsLevel = CountWhiteSpaces()) > wsLevel)
        {
            if (TryMatchNoCapture("", skipWs: true))
            {
                SkipLine();
                continue;
            }

            var match = ParseMatch(newWsLevel);
            if (match != null)
            {
                leftRecursive.Children.Add(match);
            }
        }

        return leftRecursive;
    }

    private Comment? ParseComment(int wsLevel)
    {
        if (!SkipWhiteSpaceLevel(wsLevel) || !TryMatch("comment"))
        {
            _parseNotes.Add(Err("Failed to read comment"));
            return null;
        }

        var comment = new Comment {Diagnostics = GetDiagnostic()};
        Skip();

        SkipLine();
        while ((CountWhiteSpaces()) > wsLevel)
        {
            if (TryMatchNoCapture("", skipWs: true))
            {
                SkipLine();
                continue;
            }

            if (TryMatchNoCapture("start", skipWs: true))
            {
                Skip();
                TryMatch("start");
                comment.Start = ReadToEndOfLine().Trim();
                SkipLine();
                continue;
            }
            if (TryMatchNoCapture("end", skipWs: true))
            {
                Skip();
                TryMatch("end");
                comment.End = ReadToEndOfLine().Trim();
                SkipLine();
                continue;
            }
            Skip();
            if (TryMatchNoCapture("", skipWs: true))
            {
                return null;
            }

            var readTilEndOfLine = ReadToEndOfLine();
            _parseNotes.Add(Err($"Unknown instruction `{readTilEndOfLine}`"));
            return null;
        }

        return comment;
    }

    private Statements.Alternatives? ParseAlternatives(int wsLevel)
    {
        if (!SkipWhiteSpaceLevel(wsLevel) || !TryMatch("alternatives"))
        {
            _parseNotes.Add(Err("Failed to read alternatives"));
            return null;
        }

        var statement = new Statements.Alternatives {Diagnostics = GetDiagnostic()};

        SkipLine();
        int newWsLevel;
        while ((newWsLevel = CountWhiteSpaces()) > wsLevel)
        {
            if (TryMatchNoCapture("", skipWs: true))
            {
                SkipLine();
                continue;
            }

            if (TryMatchNoCapture("error", skipWs: true))
            {
                Skip();
                TryMatch("error");
                statement.CatchesErrors = true;
                continue;
            }

            var match = ParseMatch(newWsLevel);
            if (match != null)
            {
                statement.Matches.Add(match);
            }
        }

        return statement;
    }

    private IStatement? ParseStatement(int wsLevel)
    {
        if (TryMatchNoCapture("", skipWs: true))
        {
            Skip();
            return null;
        }

        if (TryMatchNoCapture("match", skipWs: true))
        {
            return ParseMatch(wsLevel);
        }
        if (TryMatchNoCapture("while", skipWs: true))
        {
            return ParseWhile(wsLevel);
        }
        if (TryMatchNoCapture("alternatives", skipWs: true))
        {
            return ParseAlternatives(wsLevel);
        }
        if (TryMatchNoCapture("if", skipWs: true))
        {
            return ParseIf(wsLevel);
        }
        if (TryMatchNoCapture("set", skipWs: true))
        {
            return ParseSet(wsLevel);
        }
        if (TryMatchNoCapture("get", skipWs: true))
        {
            return ParseGet(wsLevel);
        }
        if (TryMatchNoCapture("print", skipWs: true))
        {
            return ParsePrint(wsLevel);
        }
        Skip();
        if (TryMatchNoCapture("", skipWs: true))
        {
            return null;
        }

        var readTilEndOfLine = ReadToEndOfLine();
        _parseNotes.Add(Err($"Unknown instruction `{readTilEndOfLine}`"));
        return null;
    }

    private Statements.Print? ParsePrint(int wsLevel)
    {
        if (!SkipWhiteSpaceLevel(wsLevel) || !TryMatch("print"))
        {
            _parseNotes.Add(Err("Failed to read print"));
            return null;
        }

        var statement = new Statements.Print {Diagnostics = GetDiagnostic()};
        Skip();
        if (TryReadIdent(out var property))
        {
            statement.Reference = new Reference(property) {Diagnostics = GetDiagnostic()};
            References.Add(statement.Reference);
        }
        else
        {
            _parseNotes.Add(Err("Failed to read in message"));
        }

        return statement;
    }

    private Statements.Set? ParseSet(int wsLevel, bool skipWhitespace = true)
    {
        if (skipWhitespace && !SkipWhiteSpaceLevel(wsLevel))
        {
            _parseNotes.Add(Err("Failed to read set"));
            return null;
        }

        if (!skipWhitespace)
        {
            Skip();
        }

        if (!TryMatch("set"))
        {
            _parseNotes.Add(Err("Failed to read set"));
            return null;
        }

        var statement = new Statements.Set {Diagnostics = GetDiagnostic()};
        Skip();
        statement.ActiveScope = ParseActiveScope() ?? EActiveScope.auto;
        Skip();

        if (TryMatch("map"))
        {
            statement.Mode = EMode.SetMapProperty;
            if (TryReadIdent(out var property))
            {
                statement.Property = property;
            }
            else
            {
                _parseNotes.Add(Err("Failed to read in property"));
            }

            Skip();
            if (TryReadIdent(out var key))
            {
                statement.Key = key;
            }
            else
            {
                _parseNotes.Add(Err("Failed to read in key"));
            }
        }
        else if (TryMatch("list"))
        {
            if (TryReadIdent(out var ident))
            {
                statement.Property = ident;
            }
            else
            {
                _parseNotes.Add(Err("Failed to read in property"));
            }

            Skip();
            if (TryMatch("index"))
            {
                statement.Mode = EMode.SetListIndex;
                var indexValue = ParseValueExpression();
                if (indexValue is not null)
                {
                    statement.Children.Add(indexValue);
                }
            }
            else if (TryMatch("push"))
            {
                statement.Mode = EMode.SetListPush;
            }
            else
            {
                _parseNotes.Add(Err("unknown list mode"));
            }
        }
        else
        {
            statement.Mode = EMode.SetProperty;
            if (TryReadIdent(out var ident))
            {
                statement.Property = ident;
            }
            else
            {
                _parseNotes.Add(Err("Failed to read in property"));
            }
        }

        Skip();
        var value = ParseValueExpression();
        if (value is not null)
        {
            statement.Children.Add(value);
        }

        return statement;
    }

    private IStatement? ParseValueExpression()
    {
        bool TryParseNew(out IStatement? outStatement)
        {
            if (TryMatch("new"))
            {
                Skip();
                if (TryReadIdent(out var ident))
                {
                    switch (ident.ToLower())
                    {
                        case "map":
                            outStatement = new Expressions.CreateNewMap {Diagnostics = GetDiagnostic()};
                            return true;
                        case "list":
                            outStatement = new Expressions.CreateNewList {Diagnostics = GetDiagnostic()};
                            return true;
                        case "bool":
                            outStatement = new Expressions.CreateNewBoolean {Diagnostics = GetDiagnostic()};
                            return true;
                        case "character":
                            outStatement = new Expressions.CreateNewCharacter {Diagnostics = GetDiagnostic()};
                            return true;
                        case "char":
                            outStatement = new Expressions.CreateNewCharacter {Diagnostics = GetDiagnostic()};
                            return true;
                        case "number":
                            outStatement = new Expressions.CreateNewNumber {Diagnostics = GetDiagnostic()};
                            return true;
                        case "scalar":
                            outStatement = new Expressions.CreateNewNumber {Diagnostics = GetDiagnostic()};
                            return true;
                        default:
                            _parseNotes.Add(Err($"Unknown instantiable datatype '{ident}'"));
                            outStatement = null;
                            return true;
                    }
                }

                _parseNotes.Add(Err($"Failed to read in datatype"));
                outStatement = null;
                return true;
            }

            outStatement = null;
            return false;
        }

        bool TryParseScalar(out IStatement? outStatement)
        {
            if (char.IsDigit(PeekChar()))
            {
                var len = _contents[_index..].TakeWhile(char.IsDigit).Count();
                if (PeekChar() == '.')
                {
                    len++;
                    len += _contents[_index..].TakeWhile(char.IsDigit).Count();
                }

                var str = _contents[_index..(_index + len)];
                if (double.TryParse(str, out var number))
                {
                    outStatement = new Expressions.Number(number) {Diagnostics = GetDiagnostic()};
                }
                else
                {
                    _parseNotes.Add(Err("Failed to read in property"));
                    outStatement = null;
                }

                _index += len;
                _column += len;
                return true;
            }

            outStatement = null;
            return false;
        }

        bool TryParseBoolean(out IStatement? outStatement)
        {
            if (_contents.Length - _index > "true".Length && _contents[_index..(_index + "true".Length)]
                    .Equals("true", StringComparison.InvariantCultureIgnoreCase))
            {
                outStatement = new Expressions.Bool(true) {Diagnostics = GetDiagnostic()};
                _index += "true".Length;
                _column += "true".Length;
                return true;
            }

            if (_contents.Length - _index > "false".Length && _contents[_index..(_index + "false".Length)]
                    .Equals("false", StringComparison.InvariantCultureIgnoreCase))
            {
                outStatement = new Expressions.Bool(false) {Diagnostics = GetDiagnostic()};
                _index += "false".Length;
                _column += "false".Length;
                return true;
            }
            outStatement = null;
            return false;
        }

        bool TryParseChar(out IStatement? outStatement)
        {
            if (PeekChar() == '\'')
            {
                NextChar();
                outStatement = new Expressions.Character(NextChar());
                if (PeekChar() == '\'')
                {
                    NextChar();
                }
                else
                {
                    _parseNotes.Add(Err($"Expected character to be ended with `'` but got `{PeekChar()}`"));
                }

                return true;
            }

            outStatement = null;
            return false;
        }

        bool TryParseGet(out IStatement? outStatement)
        {
            if (TryMatchNoCapture("get", skipWs: false))
            {
                var get = ParseGet(0, skipWhitespace: false);
                outStatement = get;
                return true;
            }

            outStatement = null;
            return false;
        }

        bool ParseValue(out IStatement? outStatement)
        {
            if (TryParseNew(out outStatement))
            {
                return true;
            }

            if (TryParseBoolean(out outStatement))
            {
                return true;
            }

            if (TryParseGet(out outStatement))
            {
                return true;
            }

            if (TryParseScalar(out outStatement))
            {
                return true;
            }

            if (TryParseChar(out outStatement))
            {
                return true;
            }

            return false;
        }

        bool ParseLevel4(out IStatement? outStatement, IStatement? leftFold = null)
        {
            if (leftFold is null)
            {
                if (!ParseValue(out var left))
                {
                    outStatement = null;
                    return false;
                }

                Skip();
                if (TryMatch("*"))
                {
                    Skip();
                    if (!ParseValue(out var right))
                    {
                        _parseNotes.Add(Err("Missing right expression"));
                        outStatement = null;
                        return false;
                    }

                    outStatement = left is not null && right is not null
                        ? new Expressions.Multiply(left, right) {Diagnostics = GetDiagnostic()}
                        : null;
                    return outStatement is null || ParseLevel4(out outStatement, outStatement);
                }

                if (TryMatch("/"))
                {
                    Skip();
                    if (!ParseValue(out var right))
                    {
                        _parseNotes.Add(Err("Missing right expression"));
                        outStatement = null;
                        return false;
                    }

                    outStatement = left is not null && right is not null
                        ? new Expressions.Divide(left, right) {Diagnostics = GetDiagnostic()}
                        : null;
                    if (outStatement is not null)
                    {
                        return ParseLevel4(out outStatement, outStatement);
                    }

                    return true;
                }

                outStatement = left;
                return true;
            }

            if (TryMatch("*"))
            {
                Skip();
                if (!ParseValue(out var right))
                {
                    _parseNotes.Add(Err("Missing right expression"));
                    outStatement = null;
                    return false;
                }

                outStatement = right is not null
                    ? new Expressions.Multiply(leftFold, right) {Diagnostics = GetDiagnostic()}
                    : null;
                return true;
            }

            if (TryMatch("/"))
            {
                Skip();
                if (!ParseValue(out var right))
                {
                    _parseNotes.Add(Err("Missing right expression"));
                    outStatement = null;
                    return false;
                }

                outStatement = right is not null
                    ? new Expressions.Divide(leftFold, right) {Diagnostics = GetDiagnostic()}
                    : null;
                return true;
            }

            outStatement = leftFold;
            return true;
        }

        bool ParseLevel3(out IStatement? outStatement, IStatement? leftFold = null)
        {
            if (leftFold is null)
            {
                if (!ParseLevel4(out var left))
                {
                    outStatement = null;
                    return false;
                }

                Skip();
                if (TryMatch("+"))
                {
                    Skip();
                    if (!ParseLevel4(out var right))
                    {
                        _parseNotes.Add(Err("Missing right expression"));
                        outStatement = null;
                        return false;
                    }

                    outStatement = left is not null && right is not null
                        ? new Expressions.Plus(left, right) {Diagnostics = GetDiagnostic()}
                        : null;
                    if (outStatement is not null)
                    {
                        return ParseLevel3(out outStatement, outStatement);
                    }

                    return true;
                }

                if (TryMatch("-"))
                {
                    Skip();
                    if (!ParseLevel4(out var right))
                    {
                        _parseNotes.Add(Err("Missing right expression"));
                        outStatement = null;
                        return false;
                    }

                    outStatement = left is not null && right is not null
                        ? new Expressions.Minus(left, right) {Diagnostics = GetDiagnostic()}
                        : null;
                    if (outStatement is not null)
                    {
                        return ParseLevel3(out outStatement, outStatement);
                    }

                    return true;
                }

                outStatement = left;
                return true;
            }

            if (TryMatch("+"))
            {
                Skip();
                if (!ParseLevel4(out var right))
                {
                    _parseNotes.Add(Err("Missing right expression"));
                    outStatement = null;
                    return false;
                }

                outStatement = right is not null
                    ? new Expressions.Plus(leftFold, right) {Diagnostics = GetDiagnostic()}
                    : null;
                return true;
            }

            if (TryMatch("-"))
            {
                Skip();
                if (!ParseLevel4(out var right))
                {
                    _parseNotes.Add(Err("Missing right expression"));
                    outStatement = null;
                    return false;
                }

                outStatement = right is not null
                    ? new Expressions.Minus(leftFold, right) {Diagnostics = GetDiagnostic()}
                    : null;
                return true;
            }

            outStatement = leftFold;
            return true;
        }

        bool ParseLevel2(out IStatement? outStatement, IStatement? leftFold = null)
        {
            if (leftFold is null)
            {
                if (!ParseLevel3(out var left))
                {
                    outStatement = null;
                    return false;
                }

                Skip();
                if (TryMatch("!="))
                {
                    Skip();
                    if (!ParseLevel3(out var right))
                    {
                        _parseNotes.Add(Err("Missing right expression"));
                        outStatement = null;
                        return false;
                    }

                    outStatement = left is not null && right is not null
                        ? new Expressions.NotEquivalentTo(left, right) {Diagnostics = GetDiagnostic()}
                        : null;
                    return outStatement is null || ParseLevel2(out outStatement, outStatement);
                }

                if (TryMatch("=="))
                {
                    Skip();
                    if (!ParseLevel3(out var right))
                    {
                        _parseNotes.Add(Err("Missing right expression"));
                        outStatement = null;
                        return false;
                    }

                    outStatement = left is not null && right is not null
                        ? new Expressions.EquivalentTo(left, right) {Diagnostics = GetDiagnostic()}
                        : null;
                    if (outStatement is not null)
                    {
                        return ParseLevel2(out outStatement, outStatement);
                    }

                    return true;
                }

                if (TryMatch("<="))
                {
                    Skip();
                    if (!ParseLevel3(out var right))
                    {
                        _parseNotes.Add(Err("Missing right expression"));
                        outStatement = null;
                        return false;
                    }

                    outStatement = left is not null && right is not null
                        ? new Expressions.LessThenOrEqualTo(left, right) {Diagnostics = GetDiagnostic()}
                        : null;
                    if (outStatement is not null)
                    {
                        return ParseLevel2(out outStatement, outStatement);
                    }

                    return true;
                }

                if (TryMatch("<"))
                {
                    Skip();
                    if (!ParseLevel3(out var right))
                    {
                        _parseNotes.Add(Err("Missing right expression"));
                        outStatement = null;
                        return false;
                    }

                    outStatement = left is not null && right is not null
                        ? new Expressions.LessThen(left, right) {Diagnostics = GetDiagnostic()}
                        : null;
                    if (outStatement is not null)
                    {
                        return ParseLevel2(out outStatement, outStatement);
                    }

                    return true;
                }

                if (TryMatch(">="))
                {
                    Skip();
                    if (!ParseLevel3(out var right))
                    {
                        _parseNotes.Add(Err("Missing right expression"));
                        outStatement = null;
                        return false;
                    }

                    outStatement = left is not null && right is not null
                        ? new Expressions.GreaterThenOrEqualTo(left, right) {Diagnostics = GetDiagnostic()}
                        : null;
                    if (outStatement is not null)
                    {
                        return ParseLevel2(out outStatement, outStatement);
                    }

                    return true;
                }

                if (TryMatch(">"))
                {
                    Skip();
                    if (!ParseLevel3(out var right))
                    {
                        _parseNotes.Add(Err("Missing right expression"));
                        outStatement = null;
                        return false;
                    }

                    outStatement = left is not null && right is not null
                        ? new Expressions.GreaterThen(left, right) {Diagnostics = GetDiagnostic()}
                        : null;
                    if (outStatement is not null)
                    {
                        return ParseLevel2(out outStatement, outStatement);
                    }

                    return true;
                }

                outStatement = left;
                return true;
            }

            if (TryMatch("!="))
            {
                Skip();
                if (!ParseLevel3(out var right))
                {
                    _parseNotes.Add(Err("Missing right expression"));
                    outStatement = null;
                    return false;
                }

                outStatement = right is not null
                    ? new Expressions.NotEquivalentTo(leftFold, right) {Diagnostics = GetDiagnostic()}
                    : null;
                return true;
            }

            if (TryMatch("=="))
            {
                Skip();
                if (!ParseLevel3(out var right))
                {
                    _parseNotes.Add(Err("Missing right expression"));
                    outStatement = null;
                    return false;
                }

                outStatement = right is not null
                    ? new Expressions.EquivalentTo(leftFold, right) {Diagnostics = GetDiagnostic()}
                    : null;
                return true;
            }

            if (TryMatch("<="))
            {
                Skip();
                if (!ParseLevel3(out var right))
                {
                    _parseNotes.Add(Err("Missing right expression"));
                    outStatement = null;
                    return false;
                }

                outStatement = right is not null
                    ? new Expressions.LessThenOrEqualTo(leftFold, right) {Diagnostics = GetDiagnostic()}
                    : null;
                return true;
            }

            if (TryMatch("<"))
            {
                Skip();
                if (!ParseLevel3(out var right))
                {
                    _parseNotes.Add(Err("Missing right expression"));
                    outStatement = null;
                    return false;
                }

                outStatement = right is not null
                    ? new Expressions.LessThen(leftFold, right) {Diagnostics = GetDiagnostic()}
                    : null;
                return true;
            }

            if (TryMatch(">="))
            {
                Skip();
                if (!ParseLevel3(out var right))
                {
                    _parseNotes.Add(Err("Missing right expression"));
                    outStatement = null;
                    return false;
                }

                outStatement = right is not null
                    ? new Expressions.GreaterThenOrEqualTo(leftFold, right) {Diagnostics = GetDiagnostic()}
                    : null;
                return true;
            }

            if (TryMatch(">"))
            {
                Skip();
                if (!ParseLevel3(out var right))
                {
                    _parseNotes.Add(Err("Missing right expression"));
                    outStatement = null;
                    return false;
                }

                outStatement = right is not null
                    ? new Expressions.GreaterThen(leftFold, right) {Diagnostics = GetDiagnostic()}
                    : null;
                return true;
            }

            outStatement = leftFold;
            return true;
        }

        bool ParseLevel1(out IStatement? outStatement, IStatement? leftFold = null)
        {
            if (leftFold is null)
            {
                if (!ParseLevel2(out var left))
                {
                    outStatement = null;
                    return false;
                }

                Skip();
                if (TryMatch("and"))
                {
                    Skip();
                    if (!ParseLevel2(out var right))
                    {
                        _parseNotes.Add(Err("Missing right expression"));
                        outStatement = null;
                        return false;
                    }

                    outStatement = left is not null && right is not null
                        ? new Expressions.And(left, right) {Diagnostics = GetDiagnostic()}
                        : null;
                    return outStatement is null || ParseLevel1(out outStatement, outStatement);
                }

                outStatement = left;
                return true;
            }

            if (TryMatch("and"))
            {
                Skip();
                if (!ParseLevel2(out var right))
                {
                    _parseNotes.Add(Err("Missing right expression"));
                    outStatement = null;
                    return false;
                }

                outStatement = right is not null
                    ? new Expressions.And(leftFold, right) {Diagnostics = GetDiagnostic()}
                    : null;
                return true;
            }

            outStatement = leftFold;
            return true;
        }

        bool ParseLevel0(out IStatement? outStatement, IStatement? leftFold = null)
        {
            if (leftFold is null)
            {
                if (!ParseLevel1(out var left))
                {
                    outStatement = null;
                    return false;
                }

                Skip();
                if (TryMatch("or"))
                {
                    Skip();
                    if (!ParseLevel1(out var right))
                    {
                        _parseNotes.Add(Err("Missing right expression"));
                        outStatement = null;
                        return false;
                    }

                    outStatement = left is not null && right is not null
                        ? new Expressions.Or(left, right) {Diagnostics = GetDiagnostic()}
                        : null;
                    return outStatement is null || ParseLevel0(out outStatement, outStatement);
                }

                outStatement = left;
                return true;
            }

            if (TryMatch("or"))
            {
                Skip();
                if (!ParseLevel1(out var right))
                {
                    _parseNotes.Add(Err("Missing right expression"));
                    outStatement = null;
                    return false;
                }

                outStatement = right is not null
                    ? new Expressions.Or(leftFold, right) {Diagnostics = GetDiagnostic()}
                    : null;
                return true;
            }

            outStatement = leftFold;
            return true;
        }

        Skip();
        if (ParseLevel0(out var value))
        {
            return value;
        }

        _parseNotes.Add(Err("Failed to read in value expression"));
        return null;
    }

    private Statements.Get? ParseGet(int wsLevel, bool skipWhitespace = true)
    {
        if (skipWhitespace && !SkipWhiteSpaceLevel(wsLevel))
        {
            _parseNotes.Add(Err("Failed to read get"));
            return null;
        }

        if (!skipWhitespace)
        {
            Skip();
        }

        if (!TryMatch("get"))
        {
            _parseNotes.Add(Err("Failed to read get"));
            return null;
        }

        var statement = new Statements.Get {Diagnostics = GetDiagnostic()};
        Skip();
        statement.ActiveScope = ParseActiveScope() ?? EActiveScope.auto;
        Skip();

        if (TryMatch("map"))
        {
            statement.Mode = EMode.GetMapProperty;
            if (TryReadIdent(out var property))
            {
                statement.Property = property;
            }
            else
            {
                _parseNotes.Add(Err("Failed to read in property"));
            }

            Skip();
            if (TryReadIdent(out var key))
            {
                statement.Key = key;
            }
            else
            {
                _parseNotes.Add(Err("Failed to read in key"));
            }
        }
        else if (TryMatch("list"))
        {
            if (TryReadIdent(out var ident))
            {
                statement.Property = ident;
            }
            else
            {
                _parseNotes.Add(Err("Failed to read in property"));
            }

            Skip();
            if (TryMatch("index"))
            {
                statement.Mode = EMode.GetListIndex;
                var value = ParseValueExpression();
                if (value is not null)
                {
                    statement.Children.Add(value);
                }
            }
            else if (TryMatch("pop"))
            {
                statement.Mode = EMode.GetListPop;
            }
            else
            {
                _parseNotes.Add(Err("unknown list mode"));
            }
        }
        else
        {
            statement.Mode = EMode.GetProperty;
            if (TryReadIdent(out var ident))
            {
                statement.Property = ident;
            }
            else
            {
                _parseNotes.Add(Err("Failed to read in property"));
            }
        }

        return statement;
    }

    private EActiveScope? ParseActiveScope()
    {
        if (TryMatch("auto"))
        {
            return EActiveScope.auto;
        }

        if (TryMatch("local"))
        {
            return EActiveScope.local;
        }
        if (TryMatch("global"))
        {
            return EActiveScope.global;
        }
        if (TryMatch("capture"))
        {
            return EActiveScope.capture;
        }

        return null;
    }

    private Statements.Match? ParseMatch(int wsLevel, bool skipWhitespace = true, bool allowCaptures = true,
        bool allowChildren = true)
    {
        if (skipWhitespace && !SkipWhiteSpaceLevel(wsLevel))
        {
            _parseNotes.Add(Err("Failed to read match"));
            return null;
        }

        if (!skipWhitespace)
        {
            Skip();
        }

        if (!TryMatch("match"))
        {
            _parseNotes.Add(Err("Failed to read match"));
            return null;
        }

        var statement = new Statements.Match {Diagnostics = GetDiagnostic()};
        Skip();
        while (PeekChar() != '\n' && !Eof())
        {
            var part = ParseReference(allowCaptures);
            if (part != null)
            {
                statement.Matches.Add(part);
            }

            Skip();
        }

        if (allowChildren)
        {
            SkipLine();
            int newWsLevel;
            while ((newWsLevel = CountWhiteSpaces()) > wsLevel)
            {
                var subStatement = ParseStatement(newWsLevel);
                if (subStatement != null)
                {
                    statement.Children.Add(subStatement);
                }

                if (PeekChar(0) != '\n')
                {
                    SkipLine();
                }
            }
        }

        return statement;
    }

    private bool Eof()
    {
        return PeekChar() == '\0';
    }

    private Reference? ParseReference(bool allowCaptures = true, bool allowOptional = true)
    {
        Skip();
        char c;
        int index;
        var isOptional = false;
        var isCaptured = false;
        string? captureName = null;
        if (PeekChar() == '?')
        {
            if (!allowOptional)
            {
                _parseNotes.Add(Err("Optional closure is not allowed here"));
            }

            NextChar();
            isOptional = true;
        }

        if (PeekChar() == '@')
        {
            if (!allowCaptures)
            {
                _parseNotes.Add(Err("Capture closure is not allowed here"));
            }

            NextChar();
            isCaptured = true;

            if (PeekChar() == '[')
            {
                NextChar();
                index = this._index;
                while (!char.IsWhiteSpace(c = PeekChar()) && c != ']')
                {
                    NextChar();
                }

                if (c != ']')
                {
                    _parseNotes.Add(Err("Expected end of capture name closure"));
                    return null;
                }

                captureName = _contents[index..this._index];
                NextChar();
            }
        }

        index = this._index;
        while (!char.IsWhiteSpace(c = PeekChar()) && c != '\0')
        {
            NextChar();
        }

        var text = _contents[index..this._index];
        var isAlias = false;
        if (text.StartsWith('"'))
        {
            if (!text.EndsWith('"'))
            {
                _parseNotes.Add(Wrn("Alias not ending with a double quote (\")"));
            }

            text = text.Trim('"');
            isAlias = true;
        }

        if (string.IsNullOrWhiteSpace(text))
        {
            _parseNotes.Add(Err("Empty reference. "));
        }

        var reference = new Reference(text)
        {
            Diagnostics = GetDiagnostic(),
            CaptureName = captureName,
            IsCaptured = isCaptured,
            IsOptional = isOptional,
            IsAlias = isAlias
        };
        References.Add(reference);
        return reference;
    }

    private Statements.While? ParseWhile(int wsLevel)
    {
        if (!SkipWhiteSpaceLevel(wsLevel) || !TryMatch("while"))
        {
            _parseNotes.Add(Err("Failed to read while"));
            return null;
        }

        var statement = new Statements.While {Diagnostics = GetDiagnostic()};
        Skip();
        if (TryMatch("not"))
        {
            statement.Negated = true;
            Skip();
        }

        IStatement? part = null;
        if (TryMatchNoCapture("match"))
        {
            part = ParseMatch(0, skipWhitespace: false, allowCaptures: false, allowChildren: false);
        }
        else if (TryMatchNoCapture("get"))
        {
            part = ParseGet(0, skipWhitespace: false);
        }
        else if (TryMatch("eval"))
        {
            part = ParseValueExpression();
        }
        else if (TryMatch("eof"))
        {
            part = new EndOfFile();
        }
        else if (TryMatch("eol"))
        {
            part = new EndOfLine();
        }
        else
        {
            _parseNotes.Add(Err("Cannot parse while contents"));
            while (!char.IsWhiteSpace(PeekChar()))
            {
                NextChar();
            }
        }

        if (part != null)
        {
            statement.Condition = part;
        }

        Skip();
        if (PeekChar() != '\n')
        {
            if (statement.Condition is null)
            {
                _parseNotes.Add(Wrn("Content after while condition. Ignoring"));
            }

            while (PeekChar() != '\n')
            {
                NextChar();
            }
        }

        SkipLine();
        int newWsLevel;
        while ((newWsLevel = CountWhiteSpaces()) > wsLevel)
        {
            var subStatement = ParseStatement(newWsLevel);
            if (subStatement != null)
            {
                statement.Children.Add(subStatement);
            }

            if (PeekChar(0) != '\n')
            {
                SkipLine();
            }
        }

        return statement;
    }

    private Statements.If? ParseIf(int wsLevel)
    {
        if (!SkipWhiteSpaceLevel(wsLevel) || !TryMatch("if"))
        {
            _parseNotes.Add(Err("Failed to read if"));
            return null;
        }

        var statement = new Statements.If {Diagnostics = GetDiagnostic()};
        Skip();
        if (TryMatch("not"))
        {
            statement.Negated = true;
            Skip();
        }

        IStatement? part = null;
        if (TryMatchNoCapture("match"))
        {
            part = ParseMatch(0, skipWhitespace: false, allowCaptures: false, allowChildren: false);
        }
        else if (TryMatchNoCapture("get"))
        {
            part = ParseGet(0, skipWhitespace: false);
        }
        else if (TryMatch("eval"))
        {
            part = ParseValueExpression();
        }
        else
        {
            _parseNotes.Add(Err("Cannot parse if contents"));
            while (!char.IsWhiteSpace(PeekChar()))
            {
                NextChar();
            }
        }

        if (part != null)
        {
            statement.Condition = part;
        }

        Skip();
        if (PeekChar() != '\n')
        {
            if (statement.Condition is null)
            {
                _parseNotes.Add(Wrn("Content after if condition. Ignoring"));
            }

            while (PeekChar() != '\n')
            {
                NextChar();
            }
        }

        if (statement.Condition is null)
        {
            _parseNotes.Add(Err("If requires condition"));
        }

        SkipLine();
        int newWsLevel;
        while ((newWsLevel = CountWhiteSpaces()) > wsLevel)
        {
            var subStatement = ParseStatement(newWsLevel);
            if (subStatement != null)
            {
                statement.Children.Add(subStatement);
            }

            if (PeekChar(0) != '\n')
            {
                SkipLine();
            }
        }

        if (TryMatchNoCapture("else") && CountWhiteSpaces() == wsLevel)
        {
            Skip();
            TryMatch("else");
            SkipLine();
            while ((newWsLevel = CountWhiteSpaces()) > wsLevel)
            {
                var subStatement = ParseStatement(newWsLevel);
                if (subStatement != null)
                {
                    statement.Else.Add(subStatement);
                }

                if (PeekChar(0) != '\n')
                {
                    SkipLine();
                }
            }
        }

        return statement;
    }

    /// <summary>
    /// Reads in a whole <see cref="Token"/>.
    /// </summary>
    /// <param name="wsLevel">The level of whitespace this is expected to start at.</param>
    /// <returns>Either a valid token or null if something moved wrong</returns>
    private Token? ParseToken(int wsLevel)
    {
        if (!SkipWhiteSpaceLevel(wsLevel) || !TryMatch("token"))
        {
            _parseNotes.Add(Err("Failed to read token"));
            return null;
        }

        var token = new Token {Diagnostics = GetDiagnostic()};
        Skip();
        if (!TryReadIdent(out var ident))
        {
            _parseNotes.Add(Err("Missing ident"));
        }

        token.Identifier = ident;
        Skip();
        if (TryMatch(":"))
        {
            Skip();
            if (!TryReadQuotedString(out var alias))
            {
                _parseNotes.Add(Wrn("Missing alias"));
            }

            token.Alias = alias;
        }

        SkipLine();
        int newWsLevel;
        while ((newWsLevel = CountWhiteSpaces()) > wsLevel)
        {
            var res = ParseToken_Statement(newWsLevel);
            if (res != null)
            {
                token.Children.Add(res);
            }
        }

        return token;
    }

    private Diagnostic GetDiagnostic()
    {
        return new Diagnostic
        {
            Column = _column,
            Line = _line,
            File = _file ?? string.Empty,
            Offset = _index
        };
    }

    private ITokenStatement? ParseToken_Statement(int wsLevel)
    {
        if (TryMatchNoCapture("", skipWs: true))
        {
            Skip();
            return null;
        }

        if (TryMatchNoCapture("require", skipWs: true))
        {
            return ParseToken_Require(wsLevel);
        }
        if (TryMatchNoCapture("backtrack", skipWs: true))
        {
            return ParseToken_Backtrack(wsLevel);
        }
        ReadToEndOfLine();
        _parseNotes.Add(Err("Unknown instruction"));
        return null;
    }

    private Multiplicity ParseMultiplicity()
    {
        if (TryMatch("once"))
        {
            return new Multiplicity(1, GetDiagnostic());
        }

        if (TryMatch("plus"))
        {
            return new Multiplicity(1, int.MaxValue, GetDiagnostic());
        }
        var range = new Multiplicity {Diagnostics = GetDiagnostic()};
        var inclusiveFrom = true;
        switch (NextChar())
        {
            case '(':
                inclusiveFrom = false;
                break;
            case '[':
                inclusiveFrom = true;
                break;
            default:
                _parseNotes.Add(Err($"Unexpected range start `{CurrentChar()}`"));
                break;
        }

        Skip();
        if (PeekChar() == '*')
        {
            NextChar();
            range.From = int.MinValue;
        }
        else
        {
            var digits = _contents[_index..].TakeWhile(char.IsDigit).Count();
            if (digits == 0)
            {
                _parseNotes.Add(Err($"Unable to find digits for range start"));
            }
            else if (int.TryParse(_contents[_index..(digits + _index)], out var from))
            {
                range.From = inclusiveFrom ? @from : @from + 1;
                _index += digits;
            }
            else
            {
                _parseNotes.Add(Err($"Failed to parse range start `{_contents[_index..(digits + _index)]}`"));
            }
        }

        Skip();
        if (PeekChar() == ',')
        {
            NextChar();
        }
        else
        {
            _parseNotes.Add(Wrn($"Expected comma"));
        }

        Skip();
        if (PeekChar() == '*')
        {
            NextChar();
            range.To = int.MaxValue;
        }
        else
        {
            var digits = _contents[_index..].TakeWhile(char.IsDigit).Count();
            if (digits == 0)
            {
                _parseNotes.Add(Err($"Unable to find digits for range start"));
            }
            else if (int.TryParse(_contents[_index..(digits + _index)], out var to))
            {
                range.To = to;
                _index += digits;
            }
            else
            {
                _parseNotes.Add(Err($"Failed to parse range start `{_contents[_index..(digits + _index)]}`"));
            }
        }


        switch (NextChar())
        {
            case ')':
                if (range.To != int.MaxValue)
                {
                    range.To++;
                }

                break;
            case ']': break;
            default:
                _parseNotes.Add(Err($"Unexpected range end `{CurrentChar()}'"));
                break;
        }

        return range;
    }

    /// <summary>
    /// Parses the body used by <see cref="TokenStatements.Require"/> and <see cref="TokenStatements.Backtrack"/>.
    /// </summary>
    /// <param name="statements">Parts list to add parts to</param>
    /// <param name="allowAnyPlaceholder">whether the any character placeholder <code>*</code> is allowed or not.</param>
    /// <param name="allowEmptyClosure">If true, empty <code>{ }</code> are accepted as valid.</param>
    /// <param name="allowReference">If true, allows <see cref="Reference"/>s to be created.</param>
    /// <returns>whether a hard validation error occured (true) or not (false)</returns>
    private bool ParseRequireBody(ICollection<IStatement> statements, bool allowAnyPlaceholder, bool allowEmptyClosure,
        bool allowReference)
    {
        var partsStartCount = statements.Count;
        if (PeekChar() == '{' &&
            // No need to check for index since index is always valid due to peek-char == '{'
            _contents.IndexOf('\n', _index) > _contents.IndexOf('}', _index))
        {
            NextChar();
            while (PeekChar() != '}' && PeekChar() != '\n')
            {
                void HandleComma()
                {
                    var la = PeekChar();
                    switch (la)
                    {
                        case ',':
                            NextChar();
                            break;
                        case '}':
                            return;
                        default:
                            _parseNotes.Add(Err("Expected comma"));
                            break;
                    }
                }

                Skip();
                // Parse character ranges
                if (PeekChar() == '*')
                {
                    // Any character
                    if (allowAnyPlaceholder)
                    {
                        statements.Add(new AnyCharacter {Diagnostics = GetDiagnostic()});
                    }
                    else
                    {
                        _parseNotes.Add(Wrn($@"ANY placeholder '*' is not accepted here."));
                    }
                }
                else if (PeekChar(2) == '-')
                {
                    // Character Range
                    var a = NextChar();
                    NextChar();
                    var b = NextChar();
                    statements.Add(new CharacterRange(a, b, GetDiagnostic()));
                }
                else
                {
                    // Token Reference

                    if (!allowReference)
                    {
                        _parseNotes.Add(Err($@"References are not accepted here."));
                        return false;
                    }

                    var start = _index;
                    var la = PeekChar();
                    switch (la)
                    {
                        case >= 'a' and <= 'z':
                        case >= 'A' and <= 'Z':
                        case '_':
                            NextChar();
                            break;
                        case ',':
                            _parseNotes.Add(Err("Empty character range"));
                            HandleComma();
                            continue;
                        default:
                            _parseNotes.Add(Err(
                                $@"Reference starts with invalid character '{la}' while only {{ a-z, A-Z, _ }} was accepted."));
                            break;
                    }

                    while (true)
                    {
                        var c = PeekChar();
                        if (c is >= 'a' and <= 'z' or >= 'A' and <= 'Z' or >= '0' and <= '9' or '_' or '-')
                        {
                            NextChar();
                        }
                        else
                        {
                            break;
                        }
                    }

                    var length = _index - start;
                    var referenceContents = _contents.Substring(start, length);
                    PeekChar(-1);
                    if (string.IsNullOrWhiteSpace(referenceContents))
                    {
                        _parseNotes.Add(Err($@"Reference match is empty."));
                        NextChar();
                    }
                    else if (!(la is >= 'a' and <= 'z' or >= 'A' and <= 'Z' or '_'))
                    {
                        _parseNotes.Add(Err(
                            $@"Reference ends with invalid character '{la}' while only {{ a-z, A-Z, 0-9, _ }} was accepted."));
                    }

                    var reference = new Reference(referenceContents) {Diagnostics = GetDiagnostic()};
                    References.Add(reference);
                    statements.Add(reference);
                }

                Skip();
                HandleComma();
            }

            if (PeekChar() != '}')
            {
                _parseNotes.Add(Err("Closure not closed"));
            }
            else
            {
                NextChar();
            }

            if (!allowEmptyClosure && statements.Count == partsStartCount)
            {
                _parseNotes.Add(Err("Empty Closure"));
                return false;
            }
        }
        else
        {
            // Parse as wholesome token till `\n`
            var currentIndex = _index < _contents.Length ? _index : _contents.Length - 1;
            var indexOfNewLine = _index < _contents.Length ? _contents.IndexOf('\n', _index) : _contents.Length - 1;
            var requireContents = _contents.Substring(currentIndex, indexOfNewLine - currentIndex);
            _column += requireContents.Length;
            _index += requireContents.Length;
            statements.Add(new Word(requireContents.Trim()) {Diagnostics = GetDiagnostic()});
        }

        return true;
    }

    private TokenStatements.Require? ParseToken_Require(int wsLevel)
    {
        if (!SkipWhiteSpaceLevel(wsLevel) || !TryMatch("require"))
        {
            _parseNotes.Add(Err("Failed to read required"));
            return null;
        }

        var require = new TokenStatements.Require {Diagnostics = GetDiagnostic()};

        Skip();
        if (TryMatch("not"))
        {
            require.Negated = true;
            Skip();
        }

        require.Range = ParseMultiplicity();
        Skip();
        if (!ParseRequireBody(require.Parts, allowAnyPlaceholder: true, allowEmptyClosure: false,
                allowReference: true))
        {
            return null;
        }

        SkipLine();

        return require;
    }

    private TokenStatements.Backtrack? ParseToken_Backtrack(int wsLevel)
    {
        if (!SkipWhiteSpaceLevel(wsLevel) || !TryMatch("backtrack"))
        {
            _parseNotes.Add(Err("Failed to read backtrack"));
            return null;
        }

        var backtrack = new TokenStatements.Backtrack {Diagnostics = GetDiagnostic()};

        Skip();
        if (TryMatch("not"))
        {
            backtrack.Negated = true;
            Skip();
        }

        backtrack.Range = ParseMultiplicity();
        Skip();
        if (!ParseRequireBody(backtrack.Parts, allowAnyPlaceholder: false, allowEmptyClosure: false,
                allowReference: false))
        {
            return null;
        }

        SkipLine();

        return backtrack;
    }

    /// <summary>
    /// Parses in the <paramref name="contents"/>.
    /// If a <see cref="Production"/> or anything else with the same name is encountered,
    /// a <see cref="ParseNote"/> will be added, warning about it being overriden.
    /// </summary>
    /// <remarks>
    /// A failed parsing attempt might render this <see cref="Parser"/> useless, since
    /// its state might be corrupted.
    /// This method is not thread safe!
    /// </remarks>
    /// <param name="filePath"></param>
    /// <param name="contents">The XCG file contents.</param>
    /// <param name="outParseNotes">The <see cref="ParseNote"/>s collected during parsing.</param>
    /// <returns>
    /// True on success, False if one or more errors occured.
    /// <paramref name="outParseNotes"/> will contain the reason for failed parsing attempts.
    /// </returns>
    /// <exception cref="InvalidOperationException">Thrown if two or more threads try to access this method at the same time</exception>
    public bool Parse(string filePath, string contents, out IEnumerable<ParseNote> outParseNotes)
    {
        static bool SameWhitespaceStyle(string contents, ref List<ParseNote> parseNotes)
        {
            var index = -1;
            var ws = new[] {'\t', ' '};
            var spaceCharacter = '\0';
            do
            {
                // Extract next line
                var newIndex = contents.IndexOf('\n', index + 1);
                var line = newIndex == -1 ? contents[(index + 1)..] : contents[(index + 1)..newIndex];
                index = newIndex;
                // Extract starting spaces from line
                var spaces = line.TakeWhile((c) => ws.Contains(c)).ToArray();
                if (spaceCharacter == '\0')
                {
                    if (spaces.Any())
                    {
                        spaceCharacter = spaces.First();
                    }
                }

                if (spaceCharacter == '\0') continue;
                var character = spaceCharacter;
                if (spaces.All((c) => c == character)) continue;
                parseNotes.Add(new ParseNote
                    {Message = "Mixed whitespaces (tab vs space) found. Cannot Continue."});
                return false;
                    
            } while (index != -1);

            return true;
        }

        this._parseNotes = new List<ParseNote>();
        if (!SameWhitespaceStyle(contents, ref _parseNotes))
        {
            outParseNotes = _parseNotes;
            return false;
        }

        lock (this)
        {
            if (_isParsing)
            {
                throw new InvalidOperationException("Multithreading not supported.");
            }

            _isParsing = true;
        }

        try
        {
            this._contents = contents;
            _line = 1;
            _column = 1;
            _index = 0;
            _file = filePath;
            outParseNotes = _parseNotes;

            while (PeekChar() != '\0')
            {
                if (TryMatchNoCapture("", skipWs: true))
                {
                }
                else if (TryMatchNoCapture("token", skipWs: true))
                {
                    var token = ParseToken(0);
                    if (token != null)
                    {
                        Tokens.Add(token);
                    }
                }
                else if (TryMatchNoCapture("message", skipWs: true))
                {
                    var message = ParseMessage(0);
                    if (message != null)
                    {
                        Messages.Add(message);
                    }
                }
                else if (TryMatchNoCapture("set", skipWs: true))
                {
                    var set = ParseSet(0);
                    if (set != null)
                    {
                        Setters.Add(set);
                    }
                }
                else if (TryMatchNoCapture("production", skipWs: true))
                {
                    var production = ParseProduction(0);
                    if (production != null)
                    {
                        Productions.Add(production);
                    }
                }
                else if (TryMatchNoCapture("left-recursive", skipWs: true))
                {
                    var leftRecursive = ParseLeftRecursive(0);
                    if (leftRecursive != null)
                    {
                        LeftRecursiveItems.Add(leftRecursive);
                    }
                }
                else if (TryMatchNoCapture("comment", skipWs: true))
                {
                    var comment = ParseComment(0);
                    if (comment != null)
                    {
                        Comments.Add(comment);
                    }
                }
                else
                {
                    var readTilEndOfLine = ReadToEndOfLine();
                    _parseNotes.Add(Err($"Unknown instruction `{readTilEndOfLine}`"));
                }

                SkipLine();
            }

            return _parseNotes.All(q => q.Severity != ESeverity.Error);
        }
        finally
        {
            _isParsing = false;
        }
    }
}