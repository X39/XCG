using System;
using System.Collections.Generic;

namespace X39.Systems.XCG.Parsing;

public class Word : IStatement, IHasDiagnostics
{
    public string Text { get; set; }
    public Diagnostic Diagnostics { get; internal init; }

    IEnumerable<IStatement> IStatement.Statements => Array.Empty<IStatement>();

    public Word(string text)
    {
        Text = text;
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
        return $@"word: ""{Text}""";
    }
}