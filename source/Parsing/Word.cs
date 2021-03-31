namespace XCG.Parsing
{
    public class Word : IPart
    {
        public string Text { get; set; }

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