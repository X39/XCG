using System;
using System.Collections.Generic;

namespace XCG.Parsing
{
    public class Word : IStatement
    {
        public string Text { get; set; }
        public Diagnostic Diagnostics { get; internal set; }

        IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();

        public Word(string text)
        {
            this.Text = text;
        }


        public static implicit operator string(Word w)
        {
            return w.Text;
        }

        public static implicit operator Word(string s)
        {
            return new Word(s);
        }

        public override string ToString()
        {
            return $@"word: ""{this.Text}""";
        }
    }
}