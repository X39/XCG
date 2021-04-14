using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace XCG.Parsing
{
    public class Parser
    {
        #region State
        private bool isParsing = false;
        private int index = -1;
        private int line = 1;
        private int column = 1;
        private string contents = String.Empty;
        private List<ParseNote> parseNotes = new List<ParseNote>();
        private string? file;
        #endregion

        public List<Token> Tokens { get; private set; } = new List<Token>();
        public List<Reference> References { get; private set; } = new List<Reference>();
        public List<Statements.Set> Setters { get; private set; } = new List<Statements.Set>();
        public List<Message> Messages { get; private set; } = new List<Message>();
        public List<Production> Productions { get; private set; } = new List<Production>();
        public List<LeftRecursive> LeftRecursives { get; private set; } = new List<LeftRecursive>();


        private string formatted(string msg)
        {
            return $"[L{this.line}|C{this.column}] {msg}";
        }

        private ParseNote inf(string msg)
        {
            return new ParseNote
            {
                Message = this.formatted(msg),
                Severity = ESeverity.Info
            };
        }

        private ParseNote wrn(string msg)
        {
            return new ParseNote
            {
                Message = this.formatted(msg),
                Severity = ESeverity.Warning
            };
        }

        private ParseNote err(string msg)
        {
            return new ParseNote
            {
                Message = this.formatted(msg),
                Severity = ESeverity.Error
            };
        }

        /// <summary>
        /// Attempts to match the given <paramref name="expected"/>, ensuring that
        /// the following character is a whitespace character.
        /// </summary>
        /// <param name="expected">The keyword to check for</param>
        /// <param name="ingoreCase">Wether to ignore casing or not</param>
        /// <param name="skipWS">Wether to skip any possible initial whitespace</param>
        /// <returns>True if keyword was matched, false if not</returns>
        private bool TryMatchNoCapture(string expected, bool ingoreCase = true, bool skipWS = true)
        {
            int localIndex = this.index;
            var stringComparison = ingoreCase ? StringComparison.InvariantCultureIgnoreCase : StringComparison.InvariantCulture;
            if (skipWS)
            {
                this.Skip(ref localIndex);
            }
            if (this.contents.Length - localIndex > expected.Length)
            {
                if (this.contents[localIndex..(localIndex + expected.Length)].Equals(expected, stringComparison))
                {
                    if (this.contents.Length - localIndex + expected.Length > 1)
                    {
                        if (Char.IsWhiteSpace(this.contents[localIndex + expected.Length]))
                        {
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        return true;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }

        /// <summary>
        /// Peeks the offset of <paramref name="la"/> in correspondance to <see cref="index"/> character from <see cref="contents"/>
        /// </summary>
        /// <param name="la">Look-Ahead offset</param>
        /// <returns></returns>
        private char PeekChar(int la = 1)
        {
            la -= 1;
            return this.index < 0 ?
                (this.index - la < 0 ? '\0' : this.contents[this.index - la]) :
                (this.index + la < this.contents.Length ? this.contents[this.index + la] : '\0');
        }
        /// <summary>
        /// Consumes a single character from <see cref="contents"/>.
        /// </summary>
        /// <remarks>
        /// Will progress <see cref="index"/> on success.
        /// </remarks>
        /// <returns></returns>
        private char NextChar()
        {
            char c = this.PeekChar();
            switch (c)
            {
                case '\n':
                    this.line++;
                    this.column++;
                    goto default;
                default:
                    this.index++;
                    return c;
                case '\0':
                    return '\0';
            }
        }
        /// <summary>
        /// Returns the current character in <see cref="contents"/> according to <see cref="index"/>
        /// </summary>
        /// <returns></returns>
        private char CurrentChar()
        {
            return this.PeekChar();
        }

        /// <summary>
        /// Attempts to match the given <paramref name="expected"/>, ensuring that
        /// the following character is a whitespace character.
        /// </summary>
        /// <remarks>
        /// Will progress <see cref="index"/> on success.
        /// </remarks>
        /// <param name="expected">The keyword to check for</param>
        /// <param name="ingoreCase">Wether to ignore casing or not</param>
        /// <returns>True if keyword was matched, false if not</returns>
        private bool TryMatch(string expected, bool ingoreCase = true)
        {
            var stringComparison = ingoreCase ? StringComparison.InvariantCultureIgnoreCase : StringComparison.InvariantCulture;
            if (this.contents.Length - this.index > expected.Length)
            {
                if (this.contents[this.index..(this.index + expected.Length)].Equals(expected, stringComparison))
                {
                    if (this.contents.Length - this.index + expected.Length > 1)
                    {
                        if (Char.IsWhiteSpace(this.contents[this.index + expected.Length]))
                        {
                            this.index += expected.Length;
                            this.column += expected.Length;
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }
                    else
                    {
                        this.index += expected.Length;
                        this.column += expected.Length;
                        return true;
                    }
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        /// <summary>
        /// Checks and Skips the whitespace level (<paramref name="wsLevel"/>).
        /// </summary>
        /// <remarks>
        /// Will progress <see cref="index"/> on success.
        /// </remarks>
        /// <param name="wsLevel">The amount of whitespaces</param>
        /// <param name="wsChars">The characters considered whitespace</param>
        /// <returns>True if whitespace level matches, false if not</returns>
        private bool SkipWhiteSpaceLevel(int wsLevel, string wsChars = " \t")
        {
            if (this.index + wsLevel >= this.contents.Length)
            {
                return false;
            }
            for (int i = this.index; i < this.index + wsLevel; i++)
            {
                if (!wsChars.Contains(this.contents[i]))
                {
                    return false;
                }
            }
            this.index += wsLevel;
            this.column += wsLevel;
            return true;
        }
        /// <summary>
        /// Skips until a character not in <paramref name="chars"/> is encountered.
        /// </summary>
        /// <param name="chars">The characters to skip</param>
        /// <param name="localIndex">Index to progress</param>
        private void Skip(ref int localIndex, string chars = " \t\r")
        {
            for (; localIndex < this.contents.Length; localIndex++)
            {
                if (!chars.Contains(this.contents[localIndex]))
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
            int startIndex = this.index;
            char la;
            while ((la = this.PeekChar()) != '\n' && la != '\0')
            {
                this.NextChar();
            }
            int endIndex = this.index;
            return this.contents[startIndex..(endIndex - 1)];
        }
        /// <summary>
        /// Skips until a character not in <paramref name="chars"/> is encountered.
        /// If next characters equal <code>/*</code>, comment mode is enabled until <code>*/</code> is encountered.
        /// </summary>
        /// <remarks>
        /// Will progress <see cref="index"/>.
        /// </remarks>
        /// <param name="chars">The characters to skip</param>
        private void Skip(string chars = " \t\r")
        {
            char la;
            bool commentMode = false;
            while ((la = this.PeekChar()) != '\0')
            {
                if (commentMode)
                {
                    if (la == '*' && this.PeekChar(2) == '/')
                    {
                        this.NextChar();
                        this.NextChar();
                        commentMode = false;
                    }
                    else
                    {
                        this.NextChar();
                    }
                }
                else if (la == '/' && this.PeekChar(2) == '*')
                {
                    this.NextChar();
                    this.NextChar();
                    commentMode = true;
                }
                else if (chars.Contains(la))
                {
                    this.NextChar();
                }
                else
                {
                    break;
                }
            }
        }
        /// <summary>
        /// Skips until a character not in <paramref name="chars"/> is encountered.
        /// Will also consume a single newline and immediatly stop afterwards
        /// </summary>
        /// <remarks>
        /// Will progress <see cref="index"/>.
        /// </remarks>
        /// <param name="chars">The characters to skip</param>
        private void SkipLine(string chars = " \t\r")
        {
            this.Skip(chars);
            if (this.index < this.contents.Length && this.contents[this.index] == '\n')
            {
                this.line++;
                this.index++;
                this.column = 1;
            }
        }
        /// <summary>
        /// Counts the whitespaces following from current <see cref="index"/>.
        /// </summary>
        /// <param name="wsChars">The characters considered whitespace</param>
        /// <returns>The amount of whitespaces encountered.</returns>
        private int CountWhiteSpaces(string wsChars = " \t")
        {
            for (int i = this.index; i < this.contents.Length; i++)
            {
                if (!wsChars.Contains(this.contents[i]))
                {
                    return i - this.index;
                }
            }
            return this.contents.Length - this.index;
        }

        /// <summary>
        /// Attempts to read in an identifier conforming to `[a-zA-Z][-_a-z0-0`A-Z]*`.
        /// </summary>
        /// <remarks>
        /// Will progress <see cref="index"/> on success.
        /// </remarks>
        /// <param name="ident"></param>
        /// <returns>Returns true if an ident of >=1 is found</returns>
        private bool TryReadIdent(out string ident)
        {
            if (this.index >= this.contents.Length || !((this.contents[this.index] >= 'a' && this.contents[this.index] <= 'z') || (this.contents[this.index] >= 'A' && this.contents[this.index] <= 'Z')))
            {
                ident = String.Empty;
                return false;
            }
            int startIndex = this.index;
            this.index++;
            this.column++;
            while (this.index < this.contents.Length &&
                ((this.contents[this.index] >= 'a' && this.contents[this.index] <= 'z')
                || (this.contents[this.index] >= 'A' && this.contents[this.index] <= 'Z')
                || (this.contents[this.index] >= '0' && this.contents[this.index] <= '9')
                || this.contents[this.index] == '-'
                || this.contents[this.index] == '_'))
            {
                this.index++;
                this.column++;
            }
            ident = this.contents.Substring(startIndex, this.index - startIndex);
            return true;
        }
        /// <summary>
        /// Attempts to read in an quoted string, unescaping escaped
        /// quotes.
        /// </summary>
        /// <remarks>
        /// Will progress <see cref="index"/> on success.
        /// </remarks>
        /// <param name="quotedString"></param>
        /// <returns>Returns true if string is found and it is terminated.</returns>
        private bool TryReadQuotedString(out string quotedString)
        {
            if (this.index >= this.contents.Length || this.contents[this.index] != '"')
            {
                quotedString = String.Empty;
                return false;
            }
            int localIndex = this.index;
            localIndex++;
            int col = this.column;
            int lin = this.line;
            col++;
            var builder = new StringBuilder();
            while (localIndex < this.contents.Length)
            {
                if (this.contents[localIndex] == '"')
                {
                    if (localIndex + 1 < this.contents.Length && this.contents[localIndex + 1] == '"')
                    {
                        localIndex++;
                    }
                    else
                    {
                        break;
                    }
                }
                else if (this.contents[localIndex] == '\n')
                {
                    col = 0;
                    lin++;
                }
                builder.Append(this.contents[localIndex]);
                localIndex++;
                col++;
            }
            if (localIndex < this.contents.Length && this.contents[localIndex] == '"')
            {
                localIndex++;
                col++;
                this.index = localIndex;
                this.column = col;
                this.line = lin;
                quotedString = builder.ToString();
                return true;
            }
            else
            {
                quotedString = String.Empty;
                return false;
            }
        }
        /// <summary>
        /// Reads in a whole <see cref="Message"/>.
        /// </summary>
        /// <param name="wsLevel">The level of whitespace this is expected to start at.</param>
        /// <returns>Either a valid token or null if something moved wrong</returns>
        private Message? ParseMessage(int wsLevel)
        {
            if (!this.SkipWhiteSpaceLevel(wsLevel) || !this.TryMatch("message"))
            {
                this.parseNotes.Add(this.err("Failed to read token"));
                return null;
            }
            var message = new Message { Diagnostics = this.GetDiagnostic() };
            this.Skip();
            if (!this.TryReadIdent(out string? ident))
            {
                this.parseNotes.Add(this.err("Missing ident"));
            }
            message.Identifier = ident;

            this.SkipLine();
            int newWsLevel;
            while ((newWsLevel = this.CountWhiteSpaces()) > wsLevel)
            {
                this.SkipWhiteSpaceLevel(newWsLevel);
                if (this.TryMatchNoCapture(""))
                {
                }
                else if (this.TryMatch("with"))
                {
                    string? res = this.ReadToEndOfLine();
                    message.Text = res;
                }
                else if (this.TryMatch("level"))
                {
                    string? res = this.ReadToEndOfLine();
                    message.Severity = res.Trim().ToLower() switch
                    {
                        "error" => ESeverity.Error,
                        "info" => ESeverity.Info,
                        "warning" => ESeverity.Warning,
                        _ => ((Func<ESeverity>)(() =>
                        {
                            this.parseNotes.Add(this.wrn($@"Unknown level '{res}', defaulting to error."));
                            return ESeverity.Error;
                        }))()
                    };
                }
                else
                {
                    string? readTilEndOfLine = this.ReadToEndOfLine();
                    this.parseNotes.Add(this.err($"Unknown instruction `{readTilEndOfLine}`"));
                }
                this.SkipLine();
            }
            if (String.IsNullOrWhiteSpace(message.Text))
            {
                this.parseNotes.Add(this.wrn("Message has empty text."));
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
            if (!this.SkipWhiteSpaceLevel(wsLevel) || !this.TryMatch("production"))
            {
                this.parseNotes.Add(this.err("Failed to read production"));
                return null;
            }
            var production = new Production { Diagnostics = this.GetDiagnostic() };
            this.Skip();
            if (!this.TryReadIdent(out string? ident))
            {
                this.parseNotes.Add(this.err("Missing ident"));
            }
            production.Identifier = ident;

            this.SkipLine();
            int newWsLevel;
            while ((newWsLevel = this.CountWhiteSpaces()) > wsLevel)
            {
                var subStatement = this.ParseStatement(newWsLevel);
                if (subStatement != null)
                {
                    production.Statements.Add(subStatement);
                }
                if (this.PeekChar(0) != '\n')
                {
                    this.SkipLine();
                }
            }

            return production;
        }
        private LeftRecursive? ParseLeftRecursive(int wsLevel)
        {
            if (!this.SkipWhiteSpaceLevel(wsLevel) || !this.TryMatch("left-recursive"))
            {
                this.parseNotes.Add(this.err("Failed to read left-recursive"));
                return null;
            }
            var leftRecursive = new LeftRecursive { Diagnostics = this.GetDiagnostic() };
            this.Skip();
            if (!this.TryReadIdent(out string? ident))
            {
                this.parseNotes.Add(this.err("Missing ident"));
            }
            leftRecursive.Identifier = ident;

            this.SkipLine();
            int newWsLevel;
            while ((newWsLevel = this.CountWhiteSpaces()) > wsLevel)
            {
                if (this.TryMatchNoCapture("", skipWS: true))
                {
                    this.SkipLine();
                    continue;
                }
                var match = this.ParseMatch(newWsLevel);
                if (match != null)
                {
                    leftRecursive.Statements.Add(match);
                }
            }

            return leftRecursive;
        }
        private Statements.Alternatives? ParseAlternatives(int wsLevel)
        {
            if (!this.SkipWhiteSpaceLevel(wsLevel) || !this.TryMatch("alternatives"))
            {
                this.parseNotes.Add(this.err("Failed to read alternatives"));
                return null;
            }
            var statement = new Statements.Alternatives { Diagnostics = this.GetDiagnostic() };

            this.SkipLine();
            int newWsLevel;
            while ((newWsLevel = this.CountWhiteSpaces()) > wsLevel)
            {
                if (this.TryMatchNoCapture("", skipWS: true))
                {
                    this.SkipLine();
                    continue;
                }
                var match = this.ParseMatch(newWsLevel);
                if (match != null)
                {
                    statement.Matches.Add(match);
                }
            }

            return statement;
        }

        private IStatement? ParseStatement(int wsLevel)
        {
            if (this.TryMatchNoCapture("", skipWS: true))
            {
                this.Skip();
                return null;
            }
            else if (this.TryMatchNoCapture("match", skipWS: true))
            {
                return this.ParseMatch(wsLevel);
            }
            else if (this.TryMatchNoCapture("while", skipWS: true))
            {
                return this.ParseWhile(wsLevel);
            }
            else if (this.TryMatchNoCapture("alternatives", skipWS: true))
            {
                return this.ParseAlternatives(wsLevel);
            }
            else if (this.TryMatchNoCapture("if", skipWS: true))
            {
                return this.ParseIf(wsLevel);
            }
            else if (this.TryMatchNoCapture("set", skipWS: true))
            {
                return this.ParseSet(wsLevel);
            }
            else if (this.TryMatchNoCapture("get", skipWS: true))
            {
                return this.ParseGet(wsLevel);
            }
            else if (this.TryMatchNoCapture("print", skipWS: true))
            {
                return this.ParsePrint(wsLevel);
            }
            else
            {
                this.Skip();
                if (this.TryMatchNoCapture("", skipWS: true))
                {
                    return null;
                }
                string? readTilEndOfLine = this.ReadToEndOfLine();
                this.parseNotes.Add(this.err($"Unknown instruction `{readTilEndOfLine}`"));
                return null;
            }
        }
        private Statements.Print? ParsePrint(int wsLevel)
        {
            if (!this.SkipWhiteSpaceLevel(wsLevel) || !this.TryMatch("print"))
            {
                this.parseNotes.Add(this.err("Failed to read print"));
                return null;
            }
            var statement = new Statements.Print { Diagnostics = this.GetDiagnostic() };
            this.Skip();
            if (this.TryReadIdent(out string? property))
            {
                statement.Reference = new Reference(property) { Diagnostics = this.GetDiagnostic() };
                this.References.Add(statement.Reference);
            }
            else { this.parseNotes.Add(this.err("Failed to read in message")); }
            return statement;
        }
        private Statements.Set? ParseSet(int wsLevel, bool skipWhitespace = true)
        {
            if (skipWhitespace && !this.SkipWhiteSpaceLevel(wsLevel))
            {
                this.parseNotes.Add(this.err("Failed to read set"));
                return null;
            }
            else if (!skipWhitespace)
            {
                this.Skip();
            }
            if (!this.TryMatch("set"))
            {
                this.parseNotes.Add(this.err("Failed to read set"));
                return null;
            }
            var statement = new Statements.Set { Diagnostics = this.GetDiagnostic() };
            this.Skip();
            statement.ActiveScope = this.ParseActiveScope() ?? EActiveScope.auto;
            this.Skip();

            if (this.TryMatch("map"))
            {
                statement.Mode = EMode.SetMapProperty;
                if (this.TryReadIdent(out string? property)) { statement.Property = property; }
                else { this.parseNotes.Add(this.err("Failed to read in property")); }
                this.Skip();
                if (this.TryReadIdent(out string? key)) { statement.Key = key; }
                else { this.parseNotes.Add(this.err("Failed to read in key")); }
            }
            else if (this.TryMatch("list"))
            {
                if (this.TryReadIdent(out string? ident)) { statement.Property = ident; }
                else { this.parseNotes.Add(this.err("Failed to read in property")); }
                this.Skip();
                if (this.TryMatch("index"))
                {
                    statement.Mode = EMode.SetListIndex;
                    var indexValue = this.ParseValueExpression();
                    if (indexValue is not null)
                    {
                        statement.Statements.Add(indexValue);
                    }
                }
                else if (this.TryMatch("push"))
                {
                    statement.Mode = EMode.SetListPush;
                }
                else
                {
                    this.parseNotes.Add(this.err("unknown list mode"));
                }
            }
            else
            {
                statement.Mode = EMode.SetProperty;
                if (this.TryReadIdent(out string? ident)) { statement.Property = ident; }
                else { this.parseNotes.Add(this.err("Failed to read in property")); }
            }
            this.Skip();
            var value = this.ParseValueExpression();
            if (value is not null)
            {
                statement.Statements.Add(value);
            }
            return statement;
        }

        private IStatement? ParseValueExpression()
        {
            bool tryParseNew(out IStatement? value)
            {
                if (this.TryMatch("new"))
                {
                    this.Skip();
                    if (this.TryReadIdent(out string? ident))
                    {
                        switch (ident.ToLower())
                        {
                            case "map": value = new Expressions.CreateNewMap { Diagnostics = this.GetDiagnostic() }; return true;
                            case "list": value = new Expressions.CreateNewList { Diagnostics = this.GetDiagnostic() }; return true;
                            case "bool": value = new Expressions.CreateNewBoolean { Diagnostics = this.GetDiagnostic() }; return true;
                            case "character": value = new Expressions.CreateNewCharacter { Diagnostics = this.GetDiagnostic() }; return true;
                            case "char": value = new Expressions.CreateNewCharacter { Diagnostics = this.GetDiagnostic() }; return true;
                            case "number": value = new Expressions.CreateNewNumber { Diagnostics = this.GetDiagnostic() }; return true;
                            case "scalar": value = new Expressions.CreateNewNumber { Diagnostics = this.GetDiagnostic() }; return true;
                            default: this.parseNotes.Add(this.err($"Unkown instancable datatype '{ident}'")); value = null; return true;
                        }
                    }
                    else
                    {
                        this.parseNotes.Add(this.err($"Failed to read in datatype"));
                        value = null;
                        return true;
                    }
                }
                else
                {
                    value = null;
                    return false;
                }
            }
            bool tryParseScalar(out IStatement? value)
            {
                if (Char.IsDigit(this.PeekChar()))
                {
                    int len = this.contents[this.index..].TakeWhile(Char.IsDigit).Count();
                    if (this.PeekChar() == '.')
                    {
                        len++;
                        len += this.contents[this.index..].TakeWhile(Char.IsDigit).Count();
                    }
                    string? str = this.contents[this.index..(this.index + len)];
                    if (Double.TryParse(str, out double number))
                    { value = new Expressions.Number(number) { Diagnostics = this.GetDiagnostic() }; }
                    else { this.parseNotes.Add(this.err("Failed to read in property")); value = null; }
                    this.index += len;
                    this.column += len;
                    return true;
                }
                else
                {
                    value = null;
                    return false;
                }
            }
            bool tryParseBoolean(out IStatement? value)
            {
                if (this.contents.Length - this.index > "true".Length && this.contents[this.index..(this.index + "true".Length)].Equals("true", StringComparison.InvariantCultureIgnoreCase))
                {
                    value = new Expressions.Bool(true) { Diagnostics = this.GetDiagnostic() };
                    this.index += "true".Length;
                    this.column += "true".Length;
                    return true;
                }
                else if (this.contents.Length - this.index > "false".Length && this.contents[this.index..(this.index + "false".Length)].Equals("false", StringComparison.InvariantCultureIgnoreCase))
                {
                    value = new Expressions.Bool(false) { Diagnostics = this.GetDiagnostic() };
                    this.index += "false".Length;
                    this.column += "false".Length;
                    return true;
                }
                else
                {
                    value = null;
                    return false;
                }
            }
            bool tryParseChar(out IStatement? value)
            {
                if (this.PeekChar() == '\'')
                {
                    this.NextChar();
                    value = new Expressions.Character(this.NextChar());
                    if (this.PeekChar() == '\'')
                    { NextChar(); }
                    else { this.parseNotes.Add(this.err($"Expected character to be ended with `'` but got `{this.PeekChar()}`")); }
                    return true;
                }
                else
                {
                    value = null;
                    return false;
                }
            }
            bool tryParseGet(out IStatement? value)
            {
                if (this.TryMatchNoCapture("get", skipWS: false))
                {
                    var get = this.ParseGet(0, skipWhitespace: false);
                    value = get;
                    return true;
                }
                else
                {
                    value = null;
                    return false;
                }
            }
            bool parseValue(out IStatement? value)
            {
                if (tryParseNew(out value)) { return true; }
                if (tryParseBoolean(out value)) { return true; }
                if (tryParseGet(out value)) { return true; }
                if (tryParseScalar(out value)) { return true; }
                if (tryParseChar(out value)) { return true; }

                return false;
            }
            bool parseLevel4(out IStatement? value, IStatement? leftFold = null)
            {
                if (leftFold is null)
                {
                    if (!parseValue(out var left)) { value = null; return false; }
                    this.Skip();
                    if (this.TryMatch("*"))
                    {
                        this.Skip();
                        if (!parseValue(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = left is not null && right is not null ? new Expressions.Multiply(left, right) { Diagnostics = this.GetDiagnostic() } : null;
                        if (value is not null)
                        {
                            return parseLevel4(out value, value);
                        }
                        return true;
                    }
                    if (this.TryMatch("/"))
                    {
                        this.Skip();
                        if (!parseValue(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = left is not null && right is not null ? new Expressions.Divide(left, right) { Diagnostics = this.GetDiagnostic() } : null;
                        if (value is not null)
                        {
                            return parseLevel4(out value, value);
                        }
                        return true;
                    }
                    value = left;
                    return true;
                }
                else
                {
                    if (this.TryMatch("*"))
                    {
                        this.Skip();
                        if (!parseValue(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = right is not null ? new Expressions.Multiply(leftFold, right) { Diagnostics = this.GetDiagnostic() } : null;
                        return true;
                    }
                    if (this.TryMatch("/"))
                    {
                        this.Skip();
                        if (!parseValue(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = right is not null ? new Expressions.Divide(leftFold, right) { Diagnostics = this.GetDiagnostic() } : null;
                        return true;
                    }
                    value = leftFold;
                    return true;
                }
            }
            bool parseLevel3(out IStatement? value, IStatement? leftFold = null)
            {
                if (leftFold is null)
                {
                    if (!parseLevel4(out var left)) { value = null; return false; }
                    this.Skip();
                    if (this.TryMatch("+"))
                    {
                        this.Skip();
                        if (!parseLevel4(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = left is not null && right is not null ? new Expressions.Plus(left, right) { Diagnostics = this.GetDiagnostic() } : null;
                        if (value is not null)
                        {
                            return parseLevel3(out value, value);
                        }
                        return true;
                    }
                    if (this.TryMatch("-"))
                    {
                        this.Skip();
                        if (!parseLevel4(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = left is not null && right is not null ? new Expressions.Minus(left, right) { Diagnostics = this.GetDiagnostic() } : null;
                        if (value is not null)
                        {
                            return parseLevel3(out value, value);
                        }
                        return true;
                    }
                    value = left;
                    return true;
                }
                else
                {
                    if (this.TryMatch("+"))
                    {
                        this.Skip();
                        if (!parseLevel4(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = right is not null ? new Expressions.Plus(leftFold, right) { Diagnostics = this.GetDiagnostic() } : null;
                        return true;
                    }
                    if (this.TryMatch("-"))
                    {
                        this.Skip();
                        if (!parseLevel4(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = right is not null ? new Expressions.Minus(leftFold, right) { Diagnostics = this.GetDiagnostic() } : null;
                        return true;
                    }
                    value = leftFold;
                    return true;
                }
            }
            bool parseLevel2(out IStatement? value, IStatement? leftFold = null)
            {
                if (leftFold is null)
                {
                    if (!parseLevel3(out var left)) { value = null; return false; }
                    this.Skip();
                    if (this.TryMatch("!="))
                    {
                        this.Skip();
                        if (!parseLevel3(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = left is not null && right is not null ? new Expressions.NotEquivalentTo(left, right) { Diagnostics = this.GetDiagnostic() } : null;
                        if (value is not null)
                        {
                            return parseLevel2(out value, value);
                        }
                        return true;
                    }
                    if (this.TryMatch("=="))
                    {
                        this.Skip();
                        if (!parseLevel3(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = left is not null && right is not null ? new Expressions.EquivalentTo(left, right) { Diagnostics = this.GetDiagnostic() } : null;
                        if (value is not null)
                        {
                            return parseLevel2(out value, value);
                        }
                        return true;
                    }
                    if (this.TryMatch("<="))
                    {
                        this.Skip();
                        if (!parseLevel3(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = left is not null && right is not null ? new Expressions.LessThenOrEqualTo(left, right) { Diagnostics = this.GetDiagnostic() } : null;
                        if (value is not null)
                        {
                            return parseLevel2(out value, value);
                        }
                        return true;
                    }
                    if (this.TryMatch("<"))
                    {
                        this.Skip();
                        if (!parseLevel3(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = left is not null && right is not null ? new Expressions.LessThen(left, right) { Diagnostics = this.GetDiagnostic() } : null;
                        if (value is not null)
                        {
                            return parseLevel2(out value, value);
                        }
                        return true;
                    }
                    if (this.TryMatch(">="))
                    {
                        this.Skip();
                        if (!parseLevel3(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = left is not null && right is not null ? new Expressions.GreaterThenOrEqualTo(left, right) { Diagnostics = this.GetDiagnostic() } : null;
                        if (value is not null)
                        {
                            return parseLevel2(out value, value);
                        }
                        return true;
                    }
                    if (this.TryMatch(">"))
                    {
                        this.Skip();
                        if (!parseLevel3(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = left is not null && right is not null ? new Expressions.GreaterThen(left, right) { Diagnostics = this.GetDiagnostic() } : null;
                        if (value is not null)
                        {
                            return parseLevel2(out value, value);
                        }
                        return true;
                    }
                    value = left;
                    return true;
                }
                else
                {
                    if (this.TryMatch("!="))
                    {
                        this.Skip();
                        if (!parseLevel3(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = right is not null ? new Expressions.NotEquivalentTo(leftFold, right) { Diagnostics = this.GetDiagnostic() } : null;
                        return true;
                    }
                    if (this.TryMatch("=="))
                    {
                        this.Skip();
                        if (!parseLevel3(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = right is not null ? new Expressions.EquivalentTo(leftFold, right) { Diagnostics = this.GetDiagnostic() } : null;
                        return true;
                    }
                    if (this.TryMatch("<="))
                    {
                        this.Skip();
                        if (!parseLevel3(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = right is not null ? new Expressions.LessThenOrEqualTo(leftFold, right) { Diagnostics = this.GetDiagnostic() } : null;
                        return true;
                    }
                    if (this.TryMatch("<"))
                    {
                        this.Skip();
                        if (!parseLevel3(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = right is not null ? new Expressions.LessThen(leftFold, right) { Diagnostics = this.GetDiagnostic() } : null;
                        return true;
                    }
                    if (this.TryMatch(">="))
                    {
                        this.Skip();
                        if (!parseLevel3(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = right is not null ? new Expressions.GreaterThenOrEqualTo(leftFold, right) { Diagnostics = this.GetDiagnostic() } : null;
                        return true;
                    }
                    if (this.TryMatch(">"))
                    {
                        this.Skip();
                        if (!parseLevel3(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = right is not null ? new Expressions.GreaterThen(leftFold, right) { Diagnostics = this.GetDiagnostic() } : null;
                        return true;
                    }
                    value = leftFold;
                    return true;
                }
            }
            bool parseLevel1(out IStatement? value, IStatement? leftFold = null)
            {
                if (leftFold is null)
                {
                    if (!parseLevel2(out var left)) { value = null; return false; }
                    this.Skip();
                    if (this.TryMatch("and"))
                    {
                        this.Skip();
                        if (!parseLevel2(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = left is not null && right is not null ? new Expressions.And(left, right) { Diagnostics = this.GetDiagnostic() } : null;
                        if (value is not null)
                        {
                            return parseLevel1(out value, value);
                        }
                        return true;
                    }
                    value = left;
                    return true;
                }
                else
                {
                    if (this.TryMatch("and"))
                    {
                        this.Skip();
                        if (!parseLevel2(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = right is not null ? new Expressions.And(leftFold, right) { Diagnostics = this.GetDiagnostic() } : null;
                        return true;
                    }
                    value = leftFold;
                    return true;
                }
            }
            bool parseLevel0(out IStatement? value, IStatement? leftFold = null)
            {
                if (leftFold is null)
                {
                    if (!parseLevel1(out var left)) { value = null; return false; }
                    this.Skip();
                    if (this.TryMatch("or"))
                    {
                        this.Skip();
                        if (!parseLevel1(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = left is not null && right is not null ? new Expressions.Or(left, right) { Diagnostics = this.GetDiagnostic() } : null;
                        if (value is not null)
                        {
                            return parseLevel0(out value, value);
                        }
                        return true;
                    }
                    value = left;
                    return true;
                }
                else
                {
                    if (this.TryMatch("or"))
                    {
                        this.Skip();
                        if (!parseLevel1(out var right)) { this.parseNotes.Add(this.err("Missing right expression")); value = null; return false; }
                        value = right is not null ? new Expressions.Or(leftFold, right) { Diagnostics = this.GetDiagnostic() } : null;
                        return true;
                    }
                    value = leftFold;
                    return true;
                }
            }
            this.Skip();
            if (parseLevel0(out var value))
            {
                return value;
            }
            else
            {
                this.parseNotes.Add(this.err("Failed to read in value expression"));
                return null;
            }
        }

        private Statements.Get? ParseGet(int wsLevel, bool skipWhitespace = true)
        {
            if (skipWhitespace && !this.SkipWhiteSpaceLevel(wsLevel))
            {
                this.parseNotes.Add(this.err("Failed to read get"));
                return null;
            }
            else if (!skipWhitespace)
            {
                this.Skip();
            }
            if (!this.TryMatch("get"))
            {
                this.parseNotes.Add(this.err("Failed to read get"));
                return null;
            }
            var statement = new Statements.Get { Diagnostics = this.GetDiagnostic() };
            this.Skip();
            statement.ActiveScope = this.ParseActiveScope() ?? EActiveScope.auto;
            this.Skip();

            if (this.TryMatch("map"))
            {
                statement.Mode = EMode.GetMapProperty;
                if (this.TryReadIdent(out string? property)) { statement.Property = property; }
                else { this.parseNotes.Add(this.err("Failed to read in property")); }
                this.Skip();
                if (this.TryReadIdent(out string? key)) { statement.Key = key; }
                else { this.parseNotes.Add(this.err("Failed to read in key")); }
            }
            else if (this.TryMatch("list"))
            {
                if (this.TryReadIdent(out string? ident)) { statement.Property = ident; }
                else { this.parseNotes.Add(this.err("Failed to read in property")); }
                this.Skip();
                if (this.TryMatch("index"))
                {
                    statement.Mode = EMode.GetListIndex;
                    var value = this.ParseValueExpression();
                    if (value is not null)
                    {
                        statement.Statements.Add(value);
                    }
                }
                else if (this.TryMatch("pop"))
                {
                    statement.Mode = EMode.GetListPop;
                }
                else
                {
                    this.parseNotes.Add(this.err("unknown list mode"));
                }
            }
            else
            {
                statement.Mode = EMode.GetProperty;
                if (this.TryReadIdent(out string? ident)) { statement.Property = ident; }
                else { this.parseNotes.Add(this.err("Failed to read in property")); }
            }
            return statement;
        }

        private EActiveScope? ParseActiveScope()
        {
            if (this.TryMatch("auto"))
            {
                return EActiveScope.auto;
            }
            else if (this.TryMatch("local"))
            {
                return EActiveScope.local;
            }
            else if (this.TryMatch("global"))
            {
                return EActiveScope.global;
            }
            else if (this.TryMatch("capture"))
            {
                return EActiveScope.capture;
            }
            return null;
        }
        private Statements.Match? ParseMatch(int wsLevel, bool skipWhitespace = true, bool allowCaptures = true, bool allowChildren = true)
        {
            if (skipWhitespace && !this.SkipWhiteSpaceLevel(wsLevel))
            {
                this.parseNotes.Add(this.err("Failed to read match"));
                return null;
            }
            else if (!skipWhitespace)
            {
                this.Skip();
            }
            if (!this.TryMatch("match"))
            {
                this.parseNotes.Add(this.err("Failed to read match"));
                return null;
            }
            var statement = new Statements.Match { Diagnostics = this.GetDiagnostic() };
            this.Skip();
            while (this.PeekChar() != '\n' && !this.EOF())
            {
                var part = this.ParseMatchPart(allowCaptures);
                if (part != null)
                {
                    statement.Parts.Add(part);
                }
                this.Skip();
            }
            if (allowChildren)
            {
                this.SkipLine();
                int newWsLevel;
                while ((newWsLevel = this.CountWhiteSpaces()) > wsLevel)
                {
                    var subStatement = this.ParseStatement(newWsLevel);
                    if (subStatement != null)
                    {
                        statement.Statements.Add(subStatement);
                    }
                    if (this.PeekChar(0) != '\n')
                    {
                        this.SkipLine();
                    }
                }
            }
            return statement;
        }

        private bool EOF()
        {
            return this.PeekChar() == '\0';
        }

        private IMatchPart? ParseMatchPart(bool allowCaptures = true)
        {
            this.Skip();
            char c;
            int index;
            bool isOptional = false;
            bool isCaptured = false;
            string? captureName = null;
            if (this.PeekChar() == '?')
            {
                this.NextChar();
                isOptional = true;
            }
            if (this.PeekChar() == '@')
            {
                if (!allowCaptures)
                {
                    this.parseNotes.Add(this.err("Capture closure is not allowed here"));
                }
                this.NextChar();
                isCaptured = true;

                if (this.PeekChar() == '[')
                {
                    this.NextChar();
                    index = this.index;
                    while (!Char.IsWhiteSpace(c = this.PeekChar()) && c != ']')
                    {
                        this.NextChar();
                    }
                    if (c != ']')
                    {
                        this.parseNotes.Add(this.err("Expected end of capture name closure"));
                        return null;
                    }
                    captureName = this.contents[index..this.index];
                    this.NextChar();
                }
            }

            index = this.index;
            while (!Char.IsWhiteSpace(c = this.PeekChar()) && c != '\0')
            {
                this.NextChar();
            }
            string? text = this.contents[index..this.index];
            bool isAlias = false;
            if (text.StartsWith('"'))
            {
                if (!text.EndsWith('"'))
                {
                    this.parseNotes.Add(this.wrn("Alias not ending with a double quote (\")"));
                }
                text = text.Trim('"');
                isAlias = true;
            }
            var reference = new Reference(text)
            {
                Diagnostics = this.GetDiagnostic(),
                CaptureName = captureName,
                IsCaptured = isCaptured,
                IsOptional = isOptional,
                IsAlias = isAlias
            };
            this.References.Add(reference);
            return reference;
        }
        private Statements.While? ParseWhile(int wsLevel)
        {
            if (!this.SkipWhiteSpaceLevel(wsLevel) || !this.TryMatch("while"))
            {
                this.parseNotes.Add(this.err("Failed to read while"));
                return null;
            }
            var statement = new Statements.While { Diagnostics = this.GetDiagnostic() };
            this.Skip();
            if (this.TryMatch("not"))
            {
                statement.Negated = true;
                this.Skip();
            }
            while (this.PeekChar() != '\n')
            {
                IStatement? part = null;
                if (this.TryMatchNoCapture("match"))
                {
                    part = this.ParseMatch(0, skipWhitespace: false, allowCaptures: false, allowChildren: false);
                }
                else if (this.TryMatchNoCapture("get"))
                {
                    part = this.ParseGet(0, skipWhitespace: false);
                }
                else if (this.TryMatch("eval"))
                {
                    part = this.ParseValueExpression();
                }
                else
                {
                    this.parseNotes.Add(this.err("Cannot parse while contents"));
                    while (!Char.IsWhiteSpace(this.PeekChar())) { this.NextChar(); }
                }
                if (part != null)
                {
                    statement.Condition.Add(part);
                }
                this.Skip();
            }
            this.SkipLine();
            int newWsLevel;
            while ((newWsLevel = this.CountWhiteSpaces()) > wsLevel)
            {
                var subStatement = this.ParseStatement(newWsLevel);
                if (subStatement != null)
                {
                    statement.Statements.Add(subStatement);
                }
                if (this.PeekChar(0) != '\n')
                {
                    this.SkipLine();
                }
            }
            return statement;
        }
        private Statements.If? ParseIf(int wsLevel)
        {
            if (!this.SkipWhiteSpaceLevel(wsLevel) || !this.TryMatch("if"))
            {
                this.parseNotes.Add(this.err("Failed to read if"));
                return null;
            }
            var statement = new Statements.If { Diagnostics = this.GetDiagnostic() };
            this.Skip();
            if (this.TryMatch("not"))
            {
                statement.Negated = true;
                this.Skip();
            }
            while (this.PeekChar() != '\n')
            {
                IStatement? part = null;
                if (this.TryMatchNoCapture("match"))
                {
                    part = this.ParseMatch(0, skipWhitespace: false, allowCaptures: false, allowChildren: false);
                }
                else if (this.TryMatchNoCapture("get"))
                {
                    part = this.ParseGet(0, skipWhitespace: false);
                }
                else if (this.TryMatch("eval"))
                {
                    part = this.ParseValueExpression();
                }
                else
                {
                    this.parseNotes.Add(this.err("Cannot parse if contents"));
                    while (!Char.IsWhiteSpace(this.PeekChar())) { this.NextChar(); }
                }
                if (part != null)
                {
                    statement.Condition.Add(part);
                }
                this.Skip();
            }
            this.SkipLine();
            int newWsLevel;
            while ((newWsLevel = this.CountWhiteSpaces()) > wsLevel)
            {
                var subStatement = this.ParseStatement(newWsLevel);
                if (subStatement != null)
                {
                    statement.Statements.Add(subStatement);
                }
                if (this.PeekChar(0) != '\n')
                {
                    this.SkipLine();
                }
            }
            if (this.TryMatchNoCapture("else") && this.CountWhiteSpaces() == wsLevel)
            {
                this.Skip();
                this.TryMatch("else");
                this.SkipLine();
                while ((newWsLevel = this.CountWhiteSpaces()) > wsLevel)
                {
                    var subStatement = this.ParseStatement(newWsLevel);
                    if (subStatement != null)
                    {
                        statement.Else.Add(subStatement);
                    }
                    if (this.PeekChar(0) != '\n')
                    {
                        this.SkipLine();
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
            if (!this.SkipWhiteSpaceLevel(wsLevel) || !this.TryMatch("token"))
            {
                this.parseNotes.Add(this.err("Failed to read token"));
                return null;
            }
            var token = new Token { Diagnostics = this.GetDiagnostic() };
            this.Skip();
            if (!this.TryReadIdent(out string? ident))
            {
                this.parseNotes.Add(this.err("Missing ident"));
            }
            token.Identifier = ident;
            this.Skip();
            if (this.TryMatch(":"))
            {
                this.Skip();
                if (!this.TryReadQuotedString(out string? alias))
                {
                    this.parseNotes.Add(this.wrn("Missing alias"));
                }
                token.Alias = alias;
            }

            this.SkipLine();
            int newWsLevel;
            while ((newWsLevel = this.CountWhiteSpaces()) > wsLevel)
            {
                var res = this.ParseToken_Statement(newWsLevel);
                if (res != null)
                {
                    token.Statements.Add(res);
                }
            }

            return token;
        }

        private Diagnostic GetDiagnostic()
        {
            return new Diagnostic
            {
                Column = this.column,
                Line = this.line,
                File = this.file ?? String.Empty,
                Offset = this.index
            };
        }

        private ITokenStatement? ParseToken_Statement(int wsLevel)
        {
            if (this.TryMatchNoCapture("", skipWS: true))
            {
                this.Skip();
                return null;
            }
            else if (this.TryMatchNoCapture("require", skipWS: true))
            {
                return this.ParseToken_Require(wsLevel);
            }
            else if (this.TryMatchNoCapture("backtrack", skipWS: true))
            {
                return this.ParseToken_Backtrack(wsLevel);
            }
            else
            {
                string? readTilEndOfLine = this.ReadToEndOfLine();
                this.parseNotes.Add(this.err("Unknown instruction"));
                return null;
            }
        }
        private Multiplicity ParseMultiplicity()
        {
            if (this.TryMatch("once"))
            {
                return new Multiplicity(1, this.GetDiagnostic());
            }
            else if (this.TryMatch("plus"))
            {
                return new Multiplicity(1, Int32.MaxValue, this.GetDiagnostic());
            }
            else
            {
                var range = new Multiplicity { Diagnostics = this.GetDiagnostic() };
                bool inclusiveFrom = true;
                switch (this.NextChar())
                {
                    case '(': inclusiveFrom = false; break;
                    case '[': inclusiveFrom = true; break;
                    default: this.parseNotes.Add(this.err($"Unexpected range start `{this.CurrentChar()}`")); break;
                }
                this.Skip();
                if (this.PeekChar() == '*')
                {
                    this.NextChar();
                    range.From = Int32.MinValue;
                }
                else
                {
                    int digits = this.contents[this.index..].TakeWhile(Char.IsDigit).Count();
                    if (digits == 0)
                    {
                        this.parseNotes.Add(this.err($"Unable to find digits for range start"));
                    }
                    else if (Int32.TryParse(this.contents[this.index..(digits + this.index)], out int from))
                    {
                        range.From = inclusiveFrom ? from : from + 1;
                        this.index += digits;
                    }
                    else
                    {
                        this.parseNotes.Add(this.err($"Failed to parse range start `{this.contents[this.index..(digits + this.index)]}`"));
                    }
                }
                this.Skip();
                if (this.PeekChar() == ',')
                {
                    this.NextChar();
                }
                else
                {
                    this.parseNotes.Add(this.wrn($"Expected comma"));
                }
                this.Skip();
                if (this.PeekChar() == '*')
                {
                    this.NextChar();
                    range.To = Int32.MinValue;
                }
                else
                {
                    int digits = this.contents[this.index..].TakeWhile(Char.IsDigit).Count();
                    if (digits == 0)
                    {
                        this.parseNotes.Add(this.err($"Unable to find digits for range start"));
                    }
                    else if (Int32.TryParse(this.contents[this.index..(digits + this.index)], out int to))
                    {
                        range.To = to;
                        this.index += digits;
                    }
                    else
                    {
                        this.parseNotes.Add(this.err($"Failed to parse range start `{this.contents[this.index..(digits + this.index)]}`"));
                    }
                }


                switch (this.NextChar())
                {
                    case ')': range.To++; break;
                    case ']': break;
                    default: this.parseNotes.Add(this.err($"Unexpected range end `{this.CurrentChar()}'")); break;
                }
                return range;
            }
        }

        /// <summary>
        /// Parses the body used by <see cref="TokenStatements.Require"/> and <see cref="TokenStatements.Backtrack"/>.
        /// </summary>
        /// <param name="parts">Parts list to add parts to</param>
        /// <param name="allowAnyPlaceholder">Wether the any character placeholder <code>*</code> is allowed or not.</param>
        /// <param name="allowEmptyClosure">If true, empty <code>{ }</code> are accepted as valid.</param>
        /// <param name="allowReference">If true, allows <see cref="Reference"/>s to be created.</param>
        /// <returns>Wether a hard validation error occured (true) or not (false)</returns>
        private bool ParseRequireBody(List<IPart> parts, bool allowAnyPlaceholder, bool allowEmptyClosure, bool allowReference)
        {
            int partsStartCount = parts.Count;
            if (this.PeekChar() == '{' &&
                // No need to check for index since index is always valid due to peekchar == '{'
                this.contents.IndexOf('\n', this.index) > this.contents.IndexOf('}', this.index))
            {
                this.NextChar();
                while (this.PeekChar() != '}' && this.PeekChar() != '\n')
                {
                    void handleComma()
                    {
                        char la = this.PeekChar();
                        if (la == ',')
                        {
                            this.NextChar();
                        }
                        else if (la == '}')
                        {
                            return;
                        }
                        else
                        {
                            this.parseNotes.Add(this.err("Expected comma"));
                        }
                    }
                    this.Skip();
                    // Parse character ranges
                    if (this.PeekChar() == '*')
                    { // Any character
                        if (allowAnyPlaceholder)
                        {
                            parts.Add(new AnyCharacter { Diagnostics = this.GetDiagnostic() });
                        }
                        else
                        {
                            this.parseNotes.Add(this.wrn($@"ANY placeholder '*' is not accepted here."));
                        }
                    }
                    else if (this.PeekChar(2) == '-')
                    { // Character Range
                        char a = this.NextChar();
                        this.NextChar();
                        char b = this.NextChar();
                        parts.Add(new CharacterRange(a, b, this.GetDiagnostic()));
                    }
                    else
                    { // Token Reference

                        if (!allowReference)
                        {
                            this.parseNotes.Add(this.err($@"References are not accepted here."));
                            return false;
                        }
                        int start = this.index;
                        char la = this.PeekChar();
                        if ((la >= 'a' && la <= 'z') || (la >= 'A' && la <= 'Z') || la == '_')
                        {
                            this.NextChar();
                        }
                        else if (la == ',')
                        {
                            this.parseNotes.Add(this.err("Empty character range"));
                            handleComma();
                            continue;
                        }
                        else
                        {
                            this.parseNotes.Add(this.err($@"Reference starts with invalid character '{la}' while only {{ a-z, A-Z, _ }} was accepted."));
                        }
                        while (true)
                        {
                            char c = this.PeekChar();
                            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_' || c == '-')
                            {
                                this.NextChar();
                            }
                            else
                            {
                                break;
                            }
                        }
                        int length = this.index - start;
                        string? referenceContents = this.contents.Substring(start, length);
                        char lb = this.PeekChar(-1);
                        if (String.IsNullOrWhiteSpace(referenceContents))
                        {
                            this.parseNotes.Add(this.err($@"Reference match is empty."));
                            this.NextChar();
                        }
                        else if (!((la >= 'a' && la <= 'z') || (la >= 'A' && la <= 'Z') || la == '_'))
                        {
                            this.parseNotes.Add(this.err($@"Reference ends with invalid character '{la}' while only {{ a-z, A-Z, 0-9, _ }} was accepted."));
                        }
                        var reference = new Reference(referenceContents) { Diagnostics = this.GetDiagnostic() };
                        this.References.Add(reference);
                        parts.Add(reference);
                    }
                    this.Skip();
                    handleComma();
                }
                if (this.PeekChar() != '}')
                {
                    this.parseNotes.Add(this.err("Closure not closed"));
                }
                else
                {
                    this.NextChar();
                }
                if (!allowEmptyClosure && parts.Count == partsStartCount)
                {
                    this.parseNotes.Add(this.err("Empty Closure"));
                    return false;
                }
            }
            else
            {
                // Parse as wholesome token till `\n`
                int currentIndex = this.index < this.contents.Length ? this.index : this.contents.Length - 1;
                int indexOfNewLine = this.index < this.contents.Length ? this.contents.IndexOf('\n', this.index) : this.contents.Length - 1;
                string? requireContents = this.contents.Substring(currentIndex, indexOfNewLine - currentIndex);
                this.column += requireContents.Length;
                this.index += requireContents.Length;
                parts.Add(new Word(requireContents.Trim()) { Diagnostics = this.GetDiagnostic() });
            }
            return true;
        }
        private TokenStatements.Require? ParseToken_Require(int wsLevel)
        {
            if (!this.SkipWhiteSpaceLevel(wsLevel) || !this.TryMatch("require"))
            {
                this.parseNotes.Add(this.err("Failed to read required"));
                return null;
            }
            var require = new TokenStatements.Require { Diagnostics = this.GetDiagnostic() };

            this.Skip();
            if (this.TryMatch("not"))
            {
                require.Negated = true;
                this.Skip();
            }
            require.Range = this.ParseMultiplicity();
            this.Skip();
            if (!this.ParseRequireBody(require.Parts, allowAnyPlaceholder: true, allowEmptyClosure: false, allowReference: true))
            {
                return null;
            }
            this.SkipLine();

            return require;
        }
        private TokenStatements.Backtrack? ParseToken_Backtrack(int wsLevel)
        {
            if (!this.SkipWhiteSpaceLevel(wsLevel) || !this.TryMatch("backtrack"))
            {
                this.parseNotes.Add(this.err("Failed to read backtrack"));
                return null;
            }
            var backtrack = new TokenStatements.Backtrack { Diagnostics = this.GetDiagnostic() };

            this.Skip();
            if (this.TryMatch("not"))
            {
                backtrack.Negated = true;
                this.Skip();
            }
            backtrack.Range = this.ParseMultiplicity();
            this.Skip();
            if (!this.ParseRequireBody(backtrack.Parts, allowAnyPlaceholder: false, allowEmptyClosure: false, allowReference: false))
            {
                return null;
            }
            this.SkipLine();

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
        /// <param name="contents">The XCG file contents.</param>
        /// <param name="outParseNotes">The <see cref="ParseNote"/>s collected during parsing.</param>
        /// <returns>
        /// True on success, False if one or more errors occured.
        /// <paramref name="outParseNotes"/> will contain the reason for failed parsing attempts.
        /// </returns>
        /// <exception cref="InvalidOperationException">Thrown if two or more threads try to access this method at the same time</exception>
        public bool Parse(string filePath, string contents, out IEnumerable<ParseNote> outParseNotes)
        {
            lock (this)
            {
                if (this.isParsing)
                {
                    throw new InvalidOperationException("Multithreading not supported.");
                }
                this.isParsing = true;
            }
            try
            {
                this.parseNotes = new List<ParseNote>();
                this.contents = contents;
                this.line = 1;
                this.column = 1;
                this.index = 0;
                this.file = filePath;
                outParseNotes = this.parseNotes;

                while (this.PeekChar() != '\0')
                {
                    if (this.TryMatchNoCapture("", skipWS: true))
                    {
                    }
                    else if (this.TryMatchNoCapture("token", skipWS: true))
                    {
                        var token = this.ParseToken(0);
                        if (token != null)
                        {
                            this.Tokens.Add(token);
                        }
                    }
                    else if (this.TryMatchNoCapture("message", skipWS: true))
                    {
                        var message = this.ParseMessage(0);
                        if (message != null)
                        {
                            this.Messages.Add(message);
                        }
                    }
                    else if (this.TryMatchNoCapture("set", skipWS: true))
                    {
                        var set = this.ParseSet(0);
                        if (set != null)
                        {
                            this.Setters.Add(set);
                        }
                    }
                    else if (this.TryMatchNoCapture("production", skipWS: true))
                    {
                        var production = this.ParseProduction(0);
                        if (production != null)
                        {
                            this.Productions.Add(production);
                        }
                    }
                    else if (this.TryMatchNoCapture("left-recursive", skipWS: true))
                    {
                        var leftRecursive = this.ParseLeftRecursive(0);
                        if (leftRecursive != null)
                        {
                            this.LeftRecursives.Add(leftRecursive);
                        }
                    }
                    else
                    {
                        string? readTilEndOfLine = this.ReadToEndOfLine();
                        this.parseNotes.Add(this.err($"Unknown instruction `{readTilEndOfLine}`"));
                    }
                    this.SkipLine();
                }

                return !this.parseNotes.Any((q) => q.Severity == ESeverity.Error);
            }
            finally
            {
                this.isParsing = false;
            }
        }
    }
}
