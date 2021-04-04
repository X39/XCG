using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;

namespace XCG.Generators.Cpp
{
    internal class NamespaceDefinition : ICppPart, IList<ICppPart>
    {
        public string? BaseName { get; set; }
        public string Name { get; }
        public string FullName => this.BaseName is null ? this.Name : String.Concat(this.BaseName, "::", this.Name);
        public List<ICppPart> Parts { get; init; }

        public NamespaceDefinition(string name)
        {
            this.Name = name;
            this.Parts = new List<ICppPart>();
        }

        public void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
        {
            writer.Write(whitespace);
            writer.Write("namespace ");
            writer.WriteLine(this.FullName);

            writer.Write(whitespace);
            writer.WriteLine("{");

            string? subWhitespace = String.Concat(whitespace, "    ");
            foreach (var generatorPart in this.Parts)
            {
                generatorPart.BaseName = null;
                generatorPart.WriteHeader(options, writer, subWhitespace);
            }

            writer.Write(whitespace);
            writer.WriteLine("}");
        }

        public void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace)
        {
            foreach (var generatorPart in this.Parts)
            {
                generatorPart.BaseName = this.FullName;
                generatorPart.WriteImplementation(options, writer, whitespace);
            }
        }

        #region IList<ICppPart>
        public int Count => ((ICollection<ICppPart>)this.Parts).Count;

        public bool IsReadOnly => ((ICollection<ICppPart>)this.Parts).IsReadOnly;

        public ICppPart this[int index] { get => ((IList<ICppPart>)this.Parts)[index]; set => ((IList<ICppPart>)this.Parts)[index] = value; }

        public int IndexOf(ICppPart item)
        {
            return ((IList<ICppPart>)this.Parts).IndexOf(item);
        }

        public void Insert(int index, ICppPart item)
        {
            ((IList<ICppPart>)this.Parts).Insert(index, item);
        }

        public void RemoveAt(int index)
        {
            ((IList<ICppPart>)this.Parts).RemoveAt(index);
        }

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

        public bool Remove(ICppPart item)
        {
            return ((ICollection<ICppPart>)this.Parts).Remove(item);
        }

        public IEnumerator<ICppPart> GetEnumerator()
        {
            return ((IEnumerable<ICppPart>)this.Parts).GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return ((IEnumerable)this.Parts).GetEnumerator();
        }
        #endregion
    }
}
