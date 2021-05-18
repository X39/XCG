
using System;
using System.Collections.Generic;
using System.Diagnostics.Contracts;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG.Generators.Cpp
{
    internal class VariableDefinition : ICppPart, IHasName
    {
        public string? BaseName { get; set; }
        public string Name { get; set; }

        /// <summary>
        /// Initializes a value using assignment and the provided value.
        /// </summary>
        public string? DefaultValue { get; set; }

        /// <summary>
        /// Changes the initialization style to brace-initialization, passing
        /// the provided values in as comma separated list.
        /// </summary>
        public string[] Args { get; set; }
        public TypeImpl Type { get; set; }

        public VariableDefinition(EType typeImpl, string variableName)
        {
            Contract.Assert(!variableName.Contains('-'));
            Contract.Assert(!variableName.Contains('@'));
            this.Type = new TypeImpl { Type = typeImpl };
            this.Name = variableName;
            this.Args = Array.Empty<string>();
        }
        public VariableDefinition(EType typeImpl, string variableName, string defaultValue)
        {
            Contract.Assert(!variableName.Contains('-'));
            Contract.Assert(!variableName.Contains('@'));
            this.Type = new TypeImpl { Type = typeImpl };
            this.Name = variableName;
            this.DefaultValue = defaultValue;
            this.Args = Array.Empty<string>();
        }
        public VariableDefinition(EType typeImpl, string variableName, params string[] defaultValue)
        {
            Contract.Assert(!variableName.Contains('-'));
            Contract.Assert(!variableName.Contains('@'));
            this.Type = new TypeImpl { Type = typeImpl };
            this.Name = variableName;
            this.Args = defaultValue;
        }
        public VariableDefinition(string typeImpl, string variableName)
        {
            Contract.Assert(!variableName.Contains('-'));
            Contract.Assert(!variableName.Contains('@'));
            this.Type = new TypeImpl { TypeString = typeImpl };
            this.Name = variableName;
            this.Args = Array.Empty<string>();
        }
        public VariableDefinition(string typeImpl, string variableName, string defaultValue)
        {
            Contract.Assert(!variableName.Contains('-'));
            Contract.Assert(!variableName.Contains('@'));
            this.Type = new TypeImpl { TypeString = typeImpl };
            this.Name = variableName;
            this.DefaultValue = defaultValue;
            this.Args = Array.Empty<string>();
        }
        public VariableDefinition(string typeImpl, string variableName, params string[] defaultValue)
        {
            Contract.Assert(!variableName.Contains('-'));
            Contract.Assert(!variableName.Contains('@'));
            this.Type = new TypeImpl { TypeString = typeImpl };
            this.Name = variableName;
            this.Args = defaultValue;
        }
        public VariableDefinition(TypeImpl typeImpl, string variableName)
        {
            Contract.Assert(!variableName.Contains('-'));
            Contract.Assert(!variableName.Contains('@'));
            this.Type = typeImpl;
            this.Name = variableName;
            this.Args = Array.Empty<string>();
        }
        public VariableDefinition(TypeImpl typeImpl, string variableName, string defaultValue)
        {
            Contract.Assert(!variableName.Contains('-'));
            Contract.Assert(!variableName.Contains('@'));
            this.Type = typeImpl;
            this.Name = variableName;
            this.DefaultValue = defaultValue;
            this.Args = Array.Empty<string>();
        }
        public VariableDefinition(TypeImpl typeImpl, string variableName, params string[] defaultValue)
        {
            Contract.Assert(!variableName.Contains('-'));
            Contract.Assert(!variableName.Contains('@'));
            this.Type = typeImpl;
            this.Name = variableName;
            this.Args = defaultValue;
        }
        public void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
        {
        }

        public void WriteImplementation(CppOptions cppOptions, StreamWriter writer, string whitespace)
        {
            writer.Write(whitespace);
            writer.Write(Type.ToString(cppOptions));
            writer.Write(" ");
            writer.Write(Name);
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
