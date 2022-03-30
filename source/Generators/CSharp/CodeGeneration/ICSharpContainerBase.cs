using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace XCG.Generators.CSharp.CodeGeneration;

internal abstract class ICSharpContainerBase : ICSharpPart, IList<ICSharpPart>
{
    public List<ICSharpPart> Parts { get; init; } = new();


    public void Add(params ICSharpPart[] parts) => AddRange(parts);
    public void AddRange(IEnumerable<ICSharpPart> parts)
    {
        foreach (var part in parts)
        {
            Add(part);
        }
    }

    public void Add(string item)
    {
        if (Parts.LastOrDefault() is FullBody fullBody)
        {
            fullBody.Add(item);
        }
        else
        {
            Parts.Add(new FullBody { item });
        }
    }

    #region IList<ICppPart>
    public ICSharpPart this[int index] { get => ((IList<ICSharpPart>)Parts)[index]; set => ((IList<ICSharpPart>)Parts)[index] = value; }

    public int Count => ((ICollection<ICSharpPart>)Parts).Count;

    public bool IsReadOnly => ((ICollection<ICSharpPart>)Parts).IsReadOnly;

    public void Add(ICSharpPart item)
    {
        ((ICollection<ICSharpPart>)Parts).Add(item);
    }

    public void Clear()
    {
        ((ICollection<ICSharpPart>)Parts).Clear();
    }

    public bool Contains(ICSharpPart item)
    {
        return ((ICollection<ICSharpPart>)Parts).Contains(item);
    }

    public void CopyTo(ICSharpPart[] array, int arrayIndex)
    {
        ((ICollection<ICSharpPart>)Parts).CopyTo(array, arrayIndex);
    }

    public IEnumerator<ICSharpPart> GetEnumerator()
    {
        return ((IEnumerable<ICSharpPart>)Parts).GetEnumerator();
    }

    public int IndexOf(ICSharpPart item)
    {
        return ((IList<ICSharpPart>)Parts).IndexOf(item);
    }

    public void Insert(int index, ICSharpPart item)
    {
        ((IList<ICSharpPart>)Parts).Insert(index, item);
    }

    public bool Remove(ICSharpPart item)
    {
        return ((ICollection<ICSharpPart>)Parts).Remove(item);
    }

    public void RemoveAt(int index)
    {
        ((IList<ICSharpPart>)Parts).RemoveAt(index);
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        return ((IEnumerable)Parts).GetEnumerator();
    }
    #endregion
    #region ISharpPart
    public string? BaseName { get; set; }
    public abstract void WriteImplementation(CSharpOptions options, StreamWriter writer, string whitespace);
    #endregion
}