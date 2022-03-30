using System.Collections;
using System.Collections.Generic;
using System.IO;

namespace XCG.Generators.CSharp.CodeGeneration;

internal class FullBody : ICSharpPart, IList<string>
{
    private readonly List<string> _inner = new();

    #region IList<string>

    public string this[int index]
    {
        get => ((IList<string>) _inner)[index];
        set => ((IList<string>) _inner)[index] = value;
    }

    public int Count => ((ICollection<string>) _inner).Count;

    public bool IsReadOnly => ((ICollection<string>) _inner).IsReadOnly;

    public void Add(string item)
    {
        ((ICollection<string>) _inner).Add(item);
    }

    public void Clear()
    {
        ((ICollection<string>) _inner).Clear();
    }

    public bool Contains(string item)
    {
        return ((ICollection<string>) _inner).Contains(item);
    }

    public void CopyTo(string[] array, int arrayIndex)
    {
        ((ICollection<string>) _inner).CopyTo(array, arrayIndex);
    }

    public IEnumerator<string> GetEnumerator()
    {
        return ((IEnumerable<string>) _inner).GetEnumerator();
    }

    public int IndexOf(string item)
    {
        return ((IList<string>) _inner).IndexOf(item);
    }

    public void Insert(int index, string item)
    {
        ((IList<string>) _inner).Insert(index, item);
    }

    public bool Remove(string item)
    {
        return ((ICollection<string>) _inner).Remove(item);
    }

    public void RemoveAt(int index)
    {
        ((IList<string>) _inner).RemoveAt(index);
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        return ((IEnumerable) _inner).GetEnumerator();
    }

    #endregion

    #region ISharpPart

    public FullBody()
    {
    }

    public string? BaseName { get; set; }


    public void WriteImplementation(CSharpOptions options, StreamWriter writer, string whitespace)
    {
        foreach (var line in _inner)
        {
            writer.Write(whitespace);
            writer.WriteLine(line);
        }
    }

    #endregion
}