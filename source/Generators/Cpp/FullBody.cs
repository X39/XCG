using System.Collections;
using System.Collections.Generic;
using System.IO;

namespace XCG.Generators.Cpp
{
    internal class FullBody : ICppPart, IList<string>
    {
        private readonly List<string> inner = new List<string>();
        private readonly EUsage usage;

        #region IList<string>
        public string this[int index] { get => ((IList<string>)this.inner)[index]; set => ((IList<string>)this.inner)[index] = value; }

        public int Count => ((ICollection<string>)this.inner).Count;

        public bool IsReadOnly => ((ICollection<string>)this.inner).IsReadOnly;

        public void Add(string item)
        {
            ((ICollection<string>)this.inner).Add(item);
        }

        public void Clear()
        {
            ((ICollection<string>)this.inner).Clear();
        }

        public bool Contains(string item)
        {
            return ((ICollection<string>)this.inner).Contains(item);
        }

        public void CopyTo(string[] array, int arrayIndex)
        {
            ((ICollection<string>)this.inner).CopyTo(array, arrayIndex);
        }

        public IEnumerator<string> GetEnumerator()
        {
            return ((IEnumerable<string>)this.inner).GetEnumerator();
        }

        public int IndexOf(string item)
        {
            return ((IList<string>)this.inner).IndexOf(item);
        }

        public void Insert(int index, string item)
        {
            ((IList<string>)this.inner).Insert(index, item);
        }

        public bool Remove(string item)
        {
            return ((ICollection<string>)this.inner).Remove(item);
        }

        public void RemoveAt(int index)
        {
            ((IList<string>)this.inner).RemoveAt(index);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return ((IEnumerable)this.inner).GetEnumerator();
        }
        #endregion
        #region ICppPart
        public FullBody(EUsage usage = EUsage.Implementation)
        {
            this.usage = usage;
        }
        public string? BaseName { get; set; }
        public void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
        {
            if (usage.HasFlag(EUsage.Header))
            {
                foreach (var line in this.inner)
                {
                    writer.Write(whitespace);
                    writer.WriteLine(line);
                }
            }
        }
        public void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace)
        {
            if (usage.HasFlag(EUsage.Implementation))
            {
                foreach (var line in this.inner)
                {
                    writer.Write(whitespace);
                    writer.WriteLine(line);
                }
            }
        }
        #endregion
    }
}