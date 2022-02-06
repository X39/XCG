namespace XCG.Generators.Cpp;

public class TerminalColor
{
    private readonly string _data;

    private TerminalColor(string colorName)
    {
        _data = colorName;
    }

    public override string ToString() => _data;

    public static implicit operator string(TerminalColor terminalColor) => terminalColor._data;


    public static TerminalColor ForegroundBlack => new("\\u001b[30m");
    public static TerminalColor ForegroundRed => new("\\u001b[31m");
    public static TerminalColor ForegroundGreen => new("\\u001b[32m");
    public static TerminalColor ForegroundYellow => new("\\u001b[33m");
    public static TerminalColor ForegroundBlue => new("\\u001b[34m");
    public static TerminalColor ForegroundMagenta => new("\\u001b[35m");
    public static TerminalColor ForegroundCyan => new("\\u001b[36m");
    public static TerminalColor ForegroundWhite => new("\\u001b[37m");
    public static TerminalColor Reset => new("\\u001b[0m");
    public static TerminalColor ForegroundBrightBlack => new("\\u001b[30;1m");
    public static TerminalColor ForegroundBrightRed => new("\\u001b[31;1m");
    public static TerminalColor ForegroundBrightGreen => new("\\u001b[32;1m");
    public static TerminalColor ForegroundBrightYellow => new("\\u001b[33;1m");
    public static TerminalColor ForegroundBrightBlue => new("\\u001b[34;1m");
    public static TerminalColor ForegroundBrightMagenta => new("\\u001b[35;1m");
    public static TerminalColor ForegroundBrightCyan => new("\\u001b[36;1m");
    public static TerminalColor ForegroundBrightWhite => new("\\u001b[37;1m");
    public static TerminalColor BackgroundBlack => new("\\u001b[40m");
    public static TerminalColor BackgroundRed => new("\\u001b[41m");
    public static TerminalColor BackgroundGreen => new("\\u001b[42m");
    public static TerminalColor BackgroundYellow => new("\\u001b[43m");
    public static TerminalColor BackgroundBlue => new("\\u001b[44m");
    public static TerminalColor BackgroundMagenta => new("\\u001b[45m");
    public static TerminalColor BackgroundCyan => new("\\u001b[46m");
    public static TerminalColor BackgroundWhite => new("\\u001b[47m");
    public static TerminalColor BackgroundBrightBlack => new("\\u001b[40;1m");
    public static TerminalColor BackgroundBrightRed => new("\\u001b[41;1m");
    public static TerminalColor BackgroundBrightGreen => new("\\u001b[42;1m");
    public static TerminalColor BackgroundBrightYellow => new("\\u001b[43;1m");
    public static TerminalColor BackgroundBrightBlue => new("\\u001b[44;1m");
    public static TerminalColor BackgroundBrightMagenta => new("\\u001b[45;1m");
    public static TerminalColor BackgroundBrightCyan => new("\\u001b[46;1m");
    public static TerminalColor BackgroundBrightWhite => new("\\u001b[47;1m");
}