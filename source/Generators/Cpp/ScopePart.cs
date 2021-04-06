using System.Collections;
using System.Collections.Generic;
using System.IO;

namespace XCG.Generators.Cpp
{
    internal class ScopePart : ICppPart, IList<ICppPart>
    {
        private readonly List<ICppPart> inner = new List<ICppPart>();
        private readonly EUsage usage;
        #region ICppPart
        public ScopePart(EUsage usage = EUsage.Implementation)
        {
            this.usage = usage;
        }
        public string? BaseName { get; set; }
        public void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
        {
            if (usage.HasFlag(EUsage.Header))
            {
                writer.Write(whitespace);
                writer.WriteLine("{");
                var subWhitespace = string.Concat("    ", whitespace);
                foreach (var part in this.inner)
                {
                    part.WriteHeader(options, writer, subWhitespace);
                }
                writer.Write(whitespace);
                writer.WriteLine("}");
            }
        }
        public void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace)
        {
            if (usage.HasFlag(EUsage.Implementation))
            {
                writer.Write(whitespace);
                writer.WriteLine("{");
                var subWhitespace = string.Concat("    ", whitespace);
                foreach (var part in this.inner)
                {
                    part.WriteImplementation(options, writer, subWhitespace);
                }
                writer.Write(whitespace);
                writer.WriteLine("}");
            }
        }
        #endregion

        public void AddRange(IEnumerable<ICppPart> parts) => this.inner.AddRange(parts);
        #region IList<ICppPart>
        public ICppPart this[int index] { get => ((IList<ICppPart>)inner)[index]; set => ((IList<ICppPart>)inner)[index] = value; }

        public int Count => ((ICollection<ICppPart>)inner).Count;

        public bool IsReadOnly => ((ICollection<ICppPart>)inner).IsReadOnly;

        public void Add(ICppPart item)
        {
            ((ICollection<ICppPart>)inner).Add(item);
        }

        public void Clear()
        {
            ((ICollection<ICppPart>)inner).Clear();
        }

        public bool Contains(ICppPart item)
        {
            return ((ICollection<ICppPart>)inner).Contains(item);
        }

        public void CopyTo(ICppPart[] array, int arrayIndex)
        {
            ((ICollection<ICppPart>)inner).CopyTo(array, arrayIndex);
        }

        public IEnumerator<ICppPart> GetEnumerator()
        {
            return ((IEnumerable<ICppPart>)inner).GetEnumerator();
        }

        public int IndexOf(ICppPart item)
        {
            return ((IList<ICppPart>)inner).IndexOf(item);
        }

        public void Insert(int index, ICppPart item)
        {
            ((IList<ICppPart>)inner).Insert(index, item);
        }

        public bool Remove(ICppPart item)
        {
            return ((ICollection<ICppPart>)inner).Remove(item);
        }

        public void RemoveAt(int index)
        {
            ((IList<ICppPart>)inner).RemoveAt(index);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return ((IEnumerable)inner).GetEnumerator();
        }
        #endregion
    }
}