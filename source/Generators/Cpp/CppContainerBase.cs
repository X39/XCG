using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace XCG.Generators.Cpp
{
    internal abstract class CppContainerBase : ICppPart, IList<ICppPart>
    {
        public List<ICppPart> Parts { get; init; } = new List<ICppPart>();


        public void Add(params ICppPart[] parts) => this.AddRange(parts);
        public void AddRange(IEnumerable<ICppPart> parts)
        {
            foreach (var part in parts)
            {
                this.Add(part);
            }
        }

        public void Add(string item)
        {
            if (this.Parts.LastOrDefault() is FullBody fullBody)
            {
                fullBody.Add(item);
            }
            else
            {
                this.Parts.Add(new FullBody { item });
            }
        }

        #region IList<ICppPart>
        public ICppPart this[int index] { get => ((IList<ICppPart>)this.Parts)[index]; set => ((IList<ICppPart>)this.Parts)[index] = value; }

        public int Count => ((ICollection<ICppPart>)this.Parts).Count;

        public bool IsReadOnly => ((ICollection<ICppPart>)this.Parts).IsReadOnly;

        public void Add(ICppPart item)
        {
            ((ICollection<ICppPart>)this.Parts).Add(item);
        }

        public void Clear()
        {
            ((ICollection<ICppPart>)this.Parts).Clear();
        }

        public bool Contains(ICppPart item)
        {
            return ((ICollection<ICppPart>)this.Parts).Contains(item);
        }

        public void CopyTo(ICppPart[] array, int arrayIndex)
        {
            ((ICollection<ICppPart>)this.Parts).CopyTo(array, arrayIndex);
        }

        public IEnumerator<ICppPart> GetEnumerator()
        {
            return ((IEnumerable<ICppPart>)this.Parts).GetEnumerator();
        }

        public int IndexOf(ICppPart item)
        {
            return ((IList<ICppPart>)this.Parts).IndexOf(item);
        }

        public void Insert(int index, ICppPart item)
        {
            ((IList<ICppPart>)this.Parts).Insert(index, item);
        }

        public bool Remove(ICppPart item)
        {
            return ((ICollection<ICppPart>)this.Parts).Remove(item);
        }

        public void RemoveAt(int index)
        {
            ((IList<ICppPart>)this.Parts).RemoveAt(index);
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return ((IEnumerable)this.Parts).GetEnumerator();
        }
        #endregion
        #region ICppPart
        public string? BaseName { get; set; }
        public abstract void WriteHeader(CppOptions options, StreamWriter writer, string whitespace);
        public abstract void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace);
        #endregion
    }
}
