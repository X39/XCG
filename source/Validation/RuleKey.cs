using System;

namespace XCG.Validation
{
    internal struct RuleKey : IEquatable<RuleKey>
    {
        public string Realm { get; set; }
        public int Code { get; set; }

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
}
