using System.Collections;
using System.Collections.Generic;
using System.IO;

namespace XCG.Generators.CSharp.CodeGeneration;

internal class NamespaceDefinition : ICSharpPart, IList<ICSharpPart>, IHasName
{
    public string? BaseName { get; set; }
    public string Name { get; }
    public string FullName => BaseName is null ? Name : string.Concat(BaseName, ".", Name);
    public List<ICSharpPart> Parts { get; init; }

    public NamespaceDefinition(string name)
    {
        Name = name;
        Parts = new List<ICSharpPart>();
    }
    public void WriteImplementation(CSharpOptions options, StreamWriter writer, string whitespace)
    {
        writer.Write(whitespace);
        writer.Write("namespace ");
        writer.WriteLine(FullName);

        writer.Write(whitespace);
        writer.WriteLine("{");

        var subWhitespace = string.Concat(whitespace, "    ");
        foreach (var generatorPart in Parts)
        {
            generatorPart.BaseName = null;
            generatorPart.WriteImplementation(options, writer, subWhitespace);
        }

        writer.Write(whitespace);
        writer.WriteLine("}");
    }

    #region IList<ICppPart>

    public int Count => ((ICollection<ICSharpPart>) Parts).Count;

    public bool IsReadOnly => ((ICollection<ICSharpPart>) Parts).IsReadOnly;

    public ICSharpPart this[int index]
    {
        get => ((IList<ICSharpPart>) Parts)[index];
        set => ((IList<ICSharpPart>) Parts)[index] = value;
    }

    public int IndexOf(ICSharpPart item)
    {
        return ((IList<ICSharpPart>) Parts).IndexOf(item);
    }

    public void Insert(int index, ICSharpPart item)
    {
        ((IList<ICSharpPart>) Parts).Insert(index, item);
    }

    public void RemoveAt(int index)
    {
        ((IList<ICSharpPart>) Parts).RemoveAt(index);
    }

    public void Add(ICSharpPart item)
    {
        ((ICollection<ICSharpPart>) Parts).Add(item);
    }

    public void Clear()
    {
        ((ICollection<ICSharpPart>) Parts).Clear();
    }

    public bool Contains(ICSharpPart item)
    {
        return ((ICollection<ICSharpPart>) Parts).Contains(item);
    }

    public void CopyTo(ICSharpPart[] array, int arrayIndex)
    {
        ((ICollection<ICSharpPart>) Parts).CopyTo(array, arrayIndex);
    }

    public bool Remove(ICSharpPart item)
    {
        return ((ICollection<ICSharpPart>) Parts).Remove(item);
    }

    public IEnumerator<ICSharpPart> GetEnumerator()
    {
        return ((IEnumerable<ICSharpPart>) Parts).GetEnumerator();
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        return ((IEnumerable) Parts).GetEnumerator();
    }

    #endregion
}