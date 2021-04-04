
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Generators.Cpp
{
    internal class VariableDefinition : ICppPart
    {
        public string? BaseName { get; set; }
        public string VariableName { get; set; }

        /// <summary>
        /// Initializes a value using assignment and the provided value.
        /// </summary>
        public string? DefaultValue { get; set; }

        /// <summary>
        /// Changes the initialization style to brace-initialization, passing
        /// the provided values in as comma separated list.
        /// </summary>
        public string[] Args { get; set; }
        public EType Type { get; set; }

        public VariableDefinition(EType typeImpl, string variableName)
        {
            this.Type = typeImpl;
            this.VariableName = variableName;
            this.Args = Array.Empty<string>();
        }
        public VariableDefinition(EType typeImpl, string variableName, string defaultValue)
        {
            this.Type = typeImpl;
            this.VariableName = variableName;
            this.DefaultValue = defaultValue;
            this.Args = Array.Empty<string>();
        }
        public VariableDefinition(EType typeImpl, string variableName, params string[] defaultValue)
        {
            this.Type = typeImpl;
            this.VariableName = variableName;
            this.Args = defaultValue;
        }
        public void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
        {
        }

        public void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace)
        {
            writer.Write(whitespace);
            writer.Write(Type.ToString());
            writer.Write(" ");
            writer.Write(VariableName);
            if (DefaultValue is not null)
            {
                writer.Write(" = ");
                writer.Write(this.DefaultValue);
            }
            else if (this.Args.Any())
            {
                writer.Write("(");
                writer.Write(String.Join(", ", this.Args));
                writer.Write(")");
            }
            writer.WriteLine(";");
        }
    }
}
