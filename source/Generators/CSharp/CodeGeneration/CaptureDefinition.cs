using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.IO;
using System.Linq;

namespace XCG.Generators.CSharp.CodeGeneration;

internal class CaptureDefinition : ICSharpPart, IHasName
{
    public string? BaseName { get; set; }
    public List<TypeImpl> Types { get; }
    public string Name { get; }
    public bool IsSingleHit { get; set; } = true;

    /// <summary>
    /// Tells whether a given item is optional and hence should be wrapped with optional.
    /// Always false unless <see cref="Types"/> has a <see cref="List{T}.Count"/> &gt; 1.
    /// Will be ignored if <see cref="IsSingleHit"/> is false.
    /// </summary>
    private bool IsOptional { get; set; } = false;

    public CaptureDefinition(string name, params TypeImpl[] typeImpls) : this(name, typeImpls as IEnumerable<TypeImpl>) {}
    public CaptureDefinition(string name, IEnumerable<TypeImpl> typeImpls)
    {
        Contract.Assert(!name.Contains('-'));
        Contract.Assert(!name.Contains('@'));
        Name = name;
        Types = typeImpls.ToList();
    }

    public void WriteImplementation(CSharpOptions cSharpOptions, StreamWriter writer, string whitespace)
    {
        switch (Types.Count)
        {
            case 0:
                return;
            case 1:
            {
                var typeImpl = Types.First();
                writer.Write(whitespace);
                if (!IsSingleHit) { writer.Write("List<"); }
                writer.Write(typeImpl.ToString(cSharpOptions));
                if (!IsSingleHit) { writer.Write(">"); }
                writer.Write($" ");
                writer.Write(Name);
                writer.WriteLine(";");
                break;
            }
            default:
            {
                writer.Write(whitespace);
                if (!IsSingleHit) { writer.Write("List<"); }
                writer.Write($"List<");
                var isFirst = true;
                foreach (var typeImpl in Types)
                {
                    if (isFirst) { isFirst = false; } else { writer.Write(", "); }
                    writer.Write(typeImpl.ToString(cSharpOptions));
                }
                writer.Write($">");
                if (IsOptional && IsSingleHit) { writer.Write("?"); }
                if (!IsSingleHit) { writer.Write(">"); }
                writer.Write($" ");
                writer.Write(Name);
                writer.WriteLine(";");
                break;
            }
        }
    }
}