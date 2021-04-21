using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Generators.Cpp
{
    public class ReturnPart : ICppPart
    {
        public string? BaseName { get; set; }
        public EValueConstant Value { get; init; }
        public EUsage Usage { get; init; }
        public string? ValueString { get; init; }

        public ReturnPart(EUsage usage = EUsage.Implementation)
        {
            this.Value = EValueConstant.None;
            this.Usage = usage;
        }
        public ReturnPart(EValueConstant value, EUsage usage = EUsage.Implementation)
        {
            this.Value = value;
            this.Usage = usage;
        }
        public ReturnPart(string value, EUsage usage = EUsage.Implementation)
        {
            this.ValueString = value;
            this.Usage = usage;
        }
        public void WriteHeader(CppOptions cppOptions, StreamWriter writer, string whitespace)
        {
            if (this.Usage == EUsage.Header)
            {
                writer.Write(whitespace);
                if (!String.IsNullOrWhiteSpace(this.ValueString))
                {
                    writer.Write("return ");
                    writer.Write(this.ValueString);
                }
                else if (this.Value == EValueConstant.None)
                {
                    writer.Write("return");
                }
                else
                {
                    writer.Write("return ");
                    writer.Write(this.Value.ToCppString());
                }
                writer.WriteLine(";");
            }
        }

        public void WriteImplementation(CppOptions cppOptions, StreamWriter writer, string whitespace)
        {
            if (this.Usage == EUsage.Implementation)
            {
                writer.Write(whitespace);
                if (!String.IsNullOrWhiteSpace(this.ValueString))
                {
                    writer.Write("return ");
                    writer.Write(this.ValueString);
                }
                else if (this.Value == EValueConstant.None)
                {
                    writer.Write("return");
                }
                else
                {
                    writer.Write("return ");
                    writer.Write(this.Value.ToCppString());
                }
                writer.WriteLine(";");
            }
        }
    }
}
