using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;

namespace XCG.Generators.Cpp
{
    internal class MethodDefinition : ICppPart, IList<ICppPart>
    {
        public EType ReturnType { get; }
        public string? BaseName { get; set; }
        public string Name { get; }
        public string FullName => this.BaseName is null ? this.Name : String.Concat(this.BaseName, "::", this.Name);
        public IEnumerable<TypeImpl> Arguments { get; }
        public List<ICppPart> Parts { get; init; }
        public string? AfterMethodImpl { get; init; }
        public MethodDefinition(EType returnType, string name, string? afterMethodImpl, IEnumerable<TypeImpl> arguments)
        {
            this.ReturnType = returnType;
            this.AfterMethodImpl = afterMethodImpl;
            this.Name = name;
            this.Arguments = new ReadOnlyCollection<TypeImpl>(arguments.ToList());
            this.Parts = new List<ICppPart>();
        }
        public MethodDefinition(EType returnType, string name, IEnumerable<TypeImpl> arguments) : this(returnType, name, null, arguments) { }
        public MethodDefinition(EType returnType, string name) : this(returnType, name, null, Array.Empty<TypeImpl>() as IEnumerable<TypeImpl>) { }
        public MethodDefinition(EType returnType, string name, string afterMethodImpl) : this(returnType, name, afterMethodImpl, Array.Empty<TypeImpl>() as IEnumerable<TypeImpl>) { }
        public MethodDefinition(EType returnType, string name, params TypeImpl[] arguments) : this(returnType, name, null, arguments as IEnumerable<TypeImpl>) { }
        public MethodDefinition(EType returnType, string name, string afterMethodImpl, params TypeImpl[] arguments) : this(returnType, name, afterMethodImpl, arguments as IEnumerable<TypeImpl>) { }

        public void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
        {
            writer.Write(whitespace);
            writer.Write(this.ReturnType.GetCppType());
            writer.Write(" ");
            writer.Write(this.FullName);
            writer.Write("(");
            writer.Write(String.Join(", ", this.Arguments.Select((q) => q.ToString())));
            writer.WriteLine(");");
        }

        public void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace)
        {
            writer.Write(whitespace);
            writer.Write(this.ReturnType.GetCppType());
            writer.Write(" ");
            writer.Write(this.FullName);
            writer.Write("(");
            writer.Write(String.Join(", ", this.Arguments.Select((q) => q.ToString())));
            writer.Write(")");
            writer.WriteLine(this.AfterMethodImpl ?? String.Empty);

            writer.Write(whitespace);
            writer.WriteLine("{");

            var subWhitespace = String.Concat(whitespace, "    ");
            foreach (var generatorPart in this.Parts)
            {
                generatorPart.WriteImplementation(options, writer, subWhitespace);
            }

            writer.Write(whitespace);
            writer.WriteLine("}");
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
    }
}
