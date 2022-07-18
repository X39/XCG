using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.Immutable;
using System.Linq;
using X39.Util.Collections;

namespace XCG.Generators.Base;

public class Function : ICodeStatementsHost
{
    public string Identifier { get; }
    public EType ReturnType { get; }
    
    private readonly List<ICodeStatement> _statements = new();
    public IReadOnlyCollection<ICodeStatement> Statements => _statements.AsReadOnly();

    public Function(string identifier, EType returnType)
    {
        Identifier = identifier;
        ReturnType = returnType;
    }

    public Variable AddParameter(EType type, string identifier)
    {
        var variable = new Variable(this, type, identifier);
        _parameters.Add(variable);
        return variable;
    }

    private readonly List<Variable> _parameters = new();
    public IReadOnlyCollection<Variable> Parameters => _parameters.AsReadOnly();
    IEnumerator<ICodeStatement> IEnumerable<ICodeStatement>.GetEnumerator()
    {
        return _statements.GetEnumerator();
    }

    IEnumerator IEnumerable.GetEnumerator()
    {
        return ((IEnumerable) _statements).GetEnumerator();
    }

    void ICollection<ICodeStatement>.Add(ICodeStatement item)
    {
        _statements.Add(item);
    }

    void ICollection<ICodeStatement>.Clear()
    {
        _statements.Clear();
    }

    bool ICollection<ICodeStatement>.Contains(ICodeStatement item)
    {
        return _statements.Contains(item);
    }

    void ICollection<ICodeStatement>.CopyTo(ICodeStatement[] array, int arrayIndex)
    {
        _statements.CopyTo(array, arrayIndex);
    }

    bool ICollection<ICodeStatement>.Remove(ICodeStatement item)
    {
        return _statements.Remove(item);
    }

    int ICollection<ICodeStatement>.Count => _statements.Count;

    bool ICollection<ICodeStatement>.IsReadOnly => ((ICollection<ICodeStatement>) _statements).IsReadOnly;

    int IList<ICodeStatement>.IndexOf(ICodeStatement item)
    {
        return _statements.IndexOf(item);
    }

    void IList<ICodeStatement>.Insert(int index, ICodeStatement item)
    {
        _statements.Insert(index, item);
    }

    void IList<ICodeStatement>.RemoveAt(int index)
    {
        _statements.RemoveAt(index);
    }

    ICodeStatement IList<ICodeStatement>.this[int index]
    {
        get => _statements[index];
        set => _statements[index] = value;
    }

    ICodeStatementsHost ICodeStatement.Parent => this;
}