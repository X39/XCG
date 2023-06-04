using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace X39.Systems.XCG.Generators.Cpp.CodeGeneration;

internal abstract class CppContainerBase : ICppPart, IList<ICppPart>
{
    public List<ICppPart> Parts { get; init; } = new();


    public void Add(params ICppPart[] parts) => AddRange(parts);
    public void AddRange(IEnumerable<ICppPart> parts)
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
    public ICppPart this[int index] { get => ((IList<ICppPart>)Parts)[index]; set => ((IList<ICppPart>)Parts)[index] = value; }

    public int Count => ((ICollection<ICppPart>)Parts).Count;

    public bool IsReadOnly => ((ICollection<ICppPart>)Parts).IsReadOnly;

    public void Add(ICppPart item)
    {
        ((ICollection<ICppPart>)Parts).Add(item);
    }

    public void Clear()
    {
        ((ICollection<ICppPart>)Parts).Clear();
    }

    public bool Contains(ICppPart item)
    {
        return ((ICollection<ICppPart>)Parts).Contains(item);
    }

    public void CopyTo(ICppPart[] array, int arrayIndex)
    {
        ((ICollection<ICppPart>)Parts).CopyTo(array, arrayIndex);
    }

    public IEnumerator<ICppPart> GetEnumerator()
    {
        return ((IEnumerable<ICppPart>)Parts).GetEnumerator();
    }

    public int IndexOf(ICppPart item)
    {
        return ((IList<ICppPart>)Parts).IndexOf(item);
    }

    public void Insert(int index, ICppPart item)
    {
        ((IList<ICppPart>)Parts).Insert(index, item);
    }

    public bool Remove(ICppPart item)
    {
        return ((ICollection<ICppPart>)Parts).Remove(item);
    }

    public void RemoveAt(int index)
    {
        ((IList<ICppPart>)Parts).RemoveAt(index);
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        return ((IEnumerable)Parts).GetEnumerator();
    }
    #endregion
    #region ICppPart
    public string? BaseName { get; set; }
    public abstract void WriteHeader(CppOptions options, StreamWriter writer, string whitespace);
    public abstract void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace);
    #endregion
}