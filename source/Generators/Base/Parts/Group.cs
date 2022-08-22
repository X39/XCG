using System;
using System.Collections.Generic;
using JetBrains.Annotations;
using XCG.Generators.Base.Enums;

namespace XCG.Generators.Base.Parts;

[PublicAPI]
public class Group
{
    public Group(string identifier)
    {
        Identifier = identifier;
    }

    public string Identifier { get; }
    public List<Function> Functions { get; } = new();


    private readonly Dictionary<string, State> _states = new();
    public IReadOnlyCollection<State> States => _states.Values;

    public Function AddFunction(string identifier, EType returnType, Action<Function> func)
    {
        var function = new Function(identifier, returnType);
        Functions.Add(function);
        func(function);
        return function;
    }

    public State State(string identifier, EType type)
    {
        if (_states.TryGetValue(identifier, out var state))
            return state.Type != type
                ? throw new InvalidOperationException($"State type mismatch. Got {type} but expected {state.Type}.")
                : state;
        _states[identifier] = state = new State(identifier, type);
        return state;
    }
}