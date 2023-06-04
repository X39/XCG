using System.Collections;
using System.Collections.Generic;
using X39.Systems.XCG.Generators.Base.Contracts;

namespace X39.Systems.XCG.Generators.Base.Statements;

public abstract class CodeStatementHostBase : ICodeStatementsHost
{
    public ICodeStatementsHost Parent { get; }
    private readonly List<ICodeStatement> _codeStatements = new();

    public CodeStatementHostBase(ICodeStatementsHost parent)
    {
        Parent = parent;
    }

    IEnumerator<ICodeStatement> IEnumerable<ICodeStatement>.GetEnumerator()
    {
        return _codeStatements.GetEnumerator();
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        return ((IEnumerable) _codeStatements).GetEnumerator();
    }

    void ICollection<ICodeStatement>.Add(ICodeStatement item)
    {
        _codeStatements.Add(item);
    }

    void ICollection<ICodeStatement>.Clear()
    {
        _codeStatements.Clear();
    }

    bool ICollection<ICodeStatement>.Contains(ICodeStatement item)
    {
        return _codeStatements.Contains(item);
    }

    void ICollection<ICodeStatement>.CopyTo(ICodeStatement[] array, int arrayIndex)
    {
        _codeStatements.CopyTo(array, arrayIndex);
    }

    bool ICollection<ICodeStatement>.Remove(ICodeStatement item)
    {
        return _codeStatements.Remove(item);
    }

    int ICollection<ICodeStatement>.Count => _codeStatements.Count;

    bool ICollection<ICodeStatement>.IsReadOnly => ((ICollection<ICodeStatement>) _codeStatements).IsReadOnly;

    int IList<ICodeStatement>.IndexOf(ICodeStatement item)
    {
        return _codeStatements.IndexOf(item);
    }

    void IList<ICodeStatement>.Insert(int index, ICodeStatement item)
    {
        _codeStatements.Insert(index, item);
    }

    void IList<ICodeStatement>.RemoveAt(int index)
    {
        _codeStatements.RemoveAt(index);
    }

    ICodeStatement IList<ICodeStatement>.this[int index]
    {
        get => _codeStatements[index];
        set => _codeStatements[index] = value;
    }
}