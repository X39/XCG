using System.Collections;
using System.Collections.Generic;
using System.IO;

namespace X39.Systems.XCG.Generators.Cpp.CodeGeneration;

internal class NamespaceDefinition : ICppPart, IList<ICppPart>, IHasName
{
    public string? BaseName { get; set; }
    public string Name { get; }
    public string FullName => BaseName is null ? Name : string.Concat(BaseName, "::", Name);
    public List<ICppPart> Parts { get; init; }

    public NamespaceDefinition(string name)
    {
        Name = name;
        Parts = new List<ICppPart>();
    }

    public void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
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
            generatorPart.WriteHeader(options, writer, subWhitespace);
        }

        writer.Write(whitespace);
        writer.WriteLine("}");
    }

    public void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace)
    {
        foreach (var generatorPart in Parts)
        {
            generatorPart.BaseName = FullName;
            generatorPart.WriteImplementation(options, writer, whitespace);
        }
    }

    #region IList<ICppPart>

    public int Count => ((ICollection<ICppPart>) Parts).Count;

    public bool IsReadOnly => ((ICollection<ICppPart>) Parts).IsReadOnly;

    public ICppPart this[int index]
    {
        get => ((IList<ICppPart>) Parts)[index];
        set => ((IList<ICppPart>) Parts)[index] = value;
    }

    public int IndexOf(ICppPart item)
    {
        return ((IList<ICppPart>) Parts).IndexOf(item);
    }

    public void Insert(int index, ICppPart item)
    {
        ((IList<ICppPart>) Parts).Insert(index, item);
    }

    public void RemoveAt(int index)
    {
        ((IList<ICppPart>) Parts).RemoveAt(index);
    }

    public void Add(ICppPart item)
    {
        ((ICollection<ICppPart>) Parts).Add(item);
    }

    public void Clear()
    {
        ((ICollection<ICppPart>) Parts).Clear();
    }

    public bool Contains(ICppPart item)
    {
        return ((ICollection<ICppPart>) Parts).Contains(item);
    }

    public void CopyTo(ICppPart[] array, int arrayIndex)
    {
        ((ICollection<ICppPart>) Parts).CopyTo(array, arrayIndex);
    }

    public bool Remove(ICppPart item)
    {
        return ((ICollection<ICppPart>) Parts).Remove(item);
    }

    public IEnumerator<ICppPart> GetEnumerator()
    {
        return ((IEnumerable<ICppPart>) Parts).GetEnumerator();
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        return ((IEnumerable) Parts).GetEnumerator();
    }

    #endregion
}