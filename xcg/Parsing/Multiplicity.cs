﻿namespace XCG.Parsing
{
    public struct Multiplicity
    {
        /// <summary>
        /// The inclusive from value.
        /// A value of <see cref="int.MinValue"/> is considered to be negative infinity.
        /// </summary>
        public int From { get; set; }
        /// <summary>
        /// The exclusive to value.
        /// A value of <see cref="int.MaxValue"/> is considered to be positive infinity.
        /// </summary>
        public int To { get; set; }


        public bool IsOnce => this.To - this.From == 1;


        public Multiplicity(int fromInclusive, int toExclusive)
        {
            this.From = fromInclusive;
            this.To = toExclusive;
        }
        public Multiplicity(int exact)
        {
            this.From = exact;
            this.To = exact + 1;
        }
    }
}