using System;

namespace XCG.Validation
{
    internal struct RuleKey : IEquatable<RuleKey>
    {
        public string Realm { get; set; }
        public int Code { get; set; }

        public override bool Equals(object? obj)
        {
            return obj is RuleKey key && this.Equals(key);
        }

        public bool Equals(RuleKey other)
        {
            return this.Realm == other.Realm &&
                   this.Code == other.Code;
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(this.Realm, this.Code);
        }
    }
}
