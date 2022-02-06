using System;

namespace XCG.Validation;

internal readonly struct RuleKey : IEquatable<RuleKey>
{
    public string Realm { get; init; }
    public int Code { get; init; }

    public override bool Equals(object? obj)
    {
        return obj is RuleKey key && Equals(key);
    }

    public bool Equals(RuleKey other)
    {
        return Realm == other.Realm &&
               Code == other.Code;
    }

    public override int GetHashCode()
    {
        return HashCode.Combine(Realm, Code);
    }
}