using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Generators.Cpp
{
    public class TerminalColor
    {
        private readonly string data;
        private TerminalColor(string colorname) { data = colorname; }

        public override string ToString() => this.data;

        public static implicit operator string (TerminalColor terminalColor) => terminalColor.data;


        public static TerminalColor ForegroundBlack => new TerminalColor("\\u001b[30m");
        public static TerminalColor ForegroundRed => new TerminalColor("\\u001b[31m");
        public static TerminalColor ForegroundGreen => new TerminalColor("\\u001b[32m");
        public static TerminalColor ForegroundYellow => new TerminalColor("\\u001b[33m");
        public static TerminalColor ForegroundBlue => new TerminalColor("\\u001b[34m");
        public static TerminalColor ForegroundMagenta => new TerminalColor("\\u001b[35m");
        public static TerminalColor ForegroundCyan => new TerminalColor("\\u001b[36m");
        public static TerminalColor ForegroundWhite => new TerminalColor("\\u001b[37m");
        public static TerminalColor Reset => new TerminalColor("\\u001b[0m");
        public static TerminalColor ForegroundBrightBlack => new TerminalColor("\\u001b[30;1m");
        public static TerminalColor ForegroundBrightRed => new TerminalColor("\\u001b[31;1m");
        public static TerminalColor ForegroundBrightGreen => new TerminalColor("\\u001b[32;1m");
        public static TerminalColor ForegroundBrightYellow => new TerminalColor("\\u001b[33;1m");
        public static TerminalColor ForegroundBrightBlue => new TerminalColor("\\u001b[34;1m");
        public static TerminalColor ForegroundBrightMagenta => new TerminalColor("\\u001b[35;1m");
        public static TerminalColor ForegroundBrightCyan => new TerminalColor("\\u001b[36;1m");
        public static TerminalColor ForegroundBrightWhite => new TerminalColor("\\u001b[37;1m");
        public static TerminalColor BackgroundBlack => new TerminalColor("\\u001b[40m");
        public static TerminalColor BackgroundRed => new TerminalColor("\\u001b[41m");
        public static TerminalColor BackgroundGreen => new TerminalColor("\\u001b[42m");
        public static TerminalColor BackgroundYellow => new TerminalColor("\\u001b[43m");
        public static TerminalColor BackgroundBlue => new TerminalColor("\\u001b[44m");
        public static TerminalColor BackgroundMagenta => new TerminalColor("\\u001b[45m");
        public static TerminalColor BackgroundCyan => new TerminalColor("\\u001b[46m");
        public static TerminalColor BackgroundWhite => new TerminalColor("\\u001b[47m");
        public static TerminalColor BackgroundBrightBlack => new TerminalColor("\\u001b[40;1m");
        public static TerminalColor BackgroundBrightRed => new TerminalColor("\\u001b[41;1m");
        public static TerminalColor BackgroundBrightGreen => new TerminalColor("\\u001b[42;1m");
        public static TerminalColor BackgroundBrightYellow => new TerminalColor("\\u001b[43;1m");
        public static TerminalColor BackgroundBrightBlue => new TerminalColor("\\u001b[44;1m");
        public static TerminalColor BackgroundBrightMagenta => new TerminalColor("\\u001b[45;1m");
        public static TerminalColor BackgroundBrightCyan => new TerminalColor("\\u001b[46;1m");
        public static TerminalColor BackgroundBrightWhite => new TerminalColor("\\u001b[47;1m");
    }
}
