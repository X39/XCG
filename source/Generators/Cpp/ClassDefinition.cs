﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace XCG.Generators.Cpp
{
    internal class ClassDefinition : ICppPart
    {
        public string? BaseName { get; set; }
        public string Name { get; }
        public string FullName => this.BaseName is null ? this.Name : String.Concat(this.BaseName, "::", this.Name);
        public List<ICppPart> PrivateParts { get; init; }
        public List<ICppPart> ProtectedParts { get; init; }
        public List<ICppPart> PublicParts { get; init; }
        public ClassDefinition(string name)
        {
            this.Name = name;
            this.PrivateParts = new();
            this.ProtectedParts = new();
            this.PublicParts = new();
        }
        public void WriteHeader(CppOptions options, StreamWriter writer, string whitespace)
        {
            writer.Write(whitespace);
            writer.Write("class ");
            writer.WriteLine(this.FullName);

            writer.Write(whitespace);
            writer.WriteLine("{");

            string? subWhitespace = String.Concat(whitespace, "    ");
            if (this.PrivateParts.WhereIs<ClassDefinition>().Any())
            {
                writer.Write(whitespace);
                writer.WriteLine("private:");
                foreach (var generatorPart in this.PrivateParts.WhereIs<ClassDefinition>())
                {
                    writer.Write(subWhitespace);
                    writer.Write("class ");
                    writer.Write(generatorPart.Name);
                    writer.WriteLine(";");
                }
            }

            if (this.ProtectedParts.WhereIs<ClassDefinition>().Any())
            {
                writer.Write(whitespace);
                writer.WriteLine("protected:");
                foreach (var generatorPart in this.ProtectedParts.WhereIs<ClassDefinition>())
                {
                    writer.Write(subWhitespace);
                    writer.Write("class ");
                    writer.Write(generatorPart.Name);
                    writer.WriteLine(";");
                }
            }

            if (this.PublicParts.WhereIs<ClassDefinition>().Any())
            {
                writer.Write(whitespace);
                writer.WriteLine("public:");
                foreach (var generatorPart in this.PublicParts.WhereIs<ClassDefinition>())
                {
                    writer.Write(subWhitespace);
                    writer.Write("class ");
                    writer.Write(generatorPart.Name);
                    writer.WriteLine(";");
                }
            }

            if (this.PrivateParts.Any())
            {
                writer.Write(whitespace);
                writer.WriteLine("private:");
                foreach (var generatorPart in this.PrivateParts)
                {
                    generatorPart.BaseName = null;
                    generatorPart.WriteHeader(options, writer, subWhitespace);
                }
            }

            if (this.ProtectedParts.Any())
            {
                writer.Write(whitespace);
                writer.WriteLine("protected:");
                foreach (var generatorPart in this.ProtectedParts)
                {
                    generatorPart.BaseName = null;
                    generatorPart.WriteHeader(options, writer, subWhitespace);
                }
            }

            if (this.PublicParts.Any())
            {
                writer.Write(whitespace);
                writer.WriteLine("public:");
                foreach (var generatorPart in this.PublicParts)
                {
                    generatorPart.BaseName = null;
                    generatorPart.WriteHeader(options, writer, subWhitespace);
                }
            }

            writer.Write(whitespace);
            writer.WriteLine("};");
        }

        public void WriteImplementation(CppOptions options, StreamWriter writer, string whitespace)
        {
            foreach (var generatorPart in this.PrivateParts)
            {
                generatorPart.BaseName = this.FullName;
                generatorPart.WriteImplementation(options, writer, whitespace);
            }

            foreach (var generatorPart in this.ProtectedParts)
            {
                generatorPart.BaseName = this.FullName;
                generatorPart.WriteImplementation(options, writer, whitespace);
            }

            foreach (var generatorPart in this.PublicParts)
            {
                generatorPart.BaseName = this.FullName;
                generatorPart.WriteImplementation(options, writer, whitespace);
            }
        }


        public MethodDefinition CreatePrintTreeMethodDefinition(CppOptions cppOptions)
        {
            const int print_ws = 0;
            const int print_hr = 1;
            const int print_m = 2;
            const int print_bs = 3;
            string n = "->";
            var whitespaceBody = new ScopePart
            {
                $@"std::vector<char> copy = v;",
                $@"if (!copy.empty())",
                $@"{{",
                $@"    bool flag = false;",
                $@"    for (auto it = copy.rbegin() + 1; it != copy.rend() && !flag; it++)",
                $@"    {{",
                $@"        switch (*it)",
                $@"        {{",
                $@"            case {print_ws}: *it = {print_m }; break;",
                $@"            case {print_bs}:",
                $@"            case {print_hr}: flag = true; break;",
                $@"        }}",
                $@"    }}",
                $@"}}",
                $@"for (auto it : copy)",
                $@"{{",
                $@"    switch (it)",
                $@"    {{",
                $@"        case {print_ws}: sstream << ' '; break;",
                $@"        case {print_hr}: sstream << '|'; break;",
                $@"        case {print_m }: sstream << '-'; break;",
                $@"        case {print_bs}: sstream << '\\'; break;",
                $@"    }}",
                $@"}}",
                $@"for (auto & it : v)",
                $@"{{",
                $@"    if (it == {print_bs})",
                $@"    {{",
                $@"        it = {print_ws};",
                $@"    }}",
                $@"}}",
            };
            var methodDefinition = new MethodDefinition(
                EType.Void, String.Concat(cppOptions.MethodsPrefix, "print_tree"),
                new ArgImpl { Name = "node", TypeString = this.FullName.ToCppSharedPtrType() },
                new ArgImpl { Name = "v", TypeString = "std::vector<char>" },
                new ArgImpl { Name = "contents", Type = EType.StringView, ReferenceCount = 1 },
                new ArgImpl { Name = "sstream", TypeString = "std::stringstream", ReferenceCount = 1 })
            {
                whitespaceBody,
                $@"sstream << ""{this.Name}:\n"";",
            };

            CaptureDefinition[] captureDefinitions = this.PublicParts.Concat(this.ProtectedParts).Concat(this.PrivateParts).WhereIs<CaptureDefinition>().ToArray();
            for (int i = 0; i < captureDefinitions.Length; i++)
            {
                IEnumerable<ICppPart> getPrintMethod(CaptureDefinition def, TypeImpl type, bool getRequired)
                {
                    var nav = $"node{n}{def.Name}";
                    if (type.TypeString is not null)
                    {
                        yield return new FullBody
                        {
                            $"{String.Concat(cppOptions.MethodsPrefix, "print_tree")}(" +
                            (getRequired ? $"std::get<{type.ToString(cppOptions)}>({nav})" : nav) +
                            $", v, contents, sstream);"
                        };
                    }
                    else
                    {
                        yield return whitespaceBody;
                        switch (type.Type)
                        {
                            default: throw new FatalException();
                            case EType.Float:
                            case EType.Boolean:
                            case EType.Double:
                            case EType.Int32:
                            case EType.Int64:
                            case EType.SizeT:
                                yield return new FullBody
                                {
                                    $@"sstream << {nav} << ""\n"";"
                                };
                                yield break;

                            case EType.OptionalBoolean:
                            case EType.OptionalFloat:
                            case EType.OptionalDouble:
                            case EType.OptionalInt32:
                            case EType.OptionalInt64:
                            case EType.OptionalSizeT:
                                yield return new FullBody
                                {
                                    $@"sstream << {nav}.value() << ""\n"";"
                                };
                                yield break;

                            case EType.String:
                            case EType.StringView:
                            case EType.Char:
                                yield return new FullBody
                                {
                                    $@"sstream << ""`"" << {nav} << ""`\n"";"
                                };
                                yield break;

                            case EType.OptionalString:
                            case EType.OptionalStringView:
                            case EType.OptionalChar:
                                yield return new FullBody
                                {
                                    $@"sstream << ""`"" << {nav}.value() << ""`\n"";"
                                };
                                yield break;

                            case EType.Token:
                                yield return new ScopePart
                                {
                                    getRequired ? $@"auto tmp = std::get<{type.ToString(cppOptions)}>({nav});" : $@"auto tmp = {nav}",
                                    $@"sstream << ""token (L"" << tmp.line << ""; C"" << tmp.column << ""; O"" << tmp.offset << "") `"" << contents.substr(tmp.offset, tmp.length) << ""`\n"";"
                                };
                                yield break;
                        }
                    }
                }
                IEnumerable<ICppPart> getWhitespaceGood(CaptureDefinition def, TypeImpl type, bool getRequired, ICppPart? success, ICppPart? failure)
                {
                    if (success is null && failure is null) { yield break; }
                    var nav = $"node{n}{def.Name}";
                    if (type.TypeString is not null)
                    {
                        yield return new IfPart(IfPart.EIfScope.If, String.Concat(success is null ? "!" : String.Empty, getRequired ? $"std::get<{type.ToString(cppOptions)}>({nav})" : nav))
                        {
                            success is null ? failure! : success
                        };
                        if (success is not null && failure is not null)
                        {
                            yield return new IfPart(IfPart.EIfScope.Else, null)
                            {
                                failure
                            };
                        }
                    }
                    else
                    {
                        switch (type.Type)
                        {
                            default: throw new FatalException();
                            case EType.Float:
                            case EType.Boolean:
                            case EType.Double:
                            case EType.Int32:
                            case EType.Int64:
                            case EType.SizeT:
                            case EType.String:
                            case EType.StringView:
                            case EType.Char:
                            case EType.Token:
                                if (success is not null)
                                {
                                    yield return success;
                                }
                                yield break;

                            case EType.OptionalBoolean:
                            case EType.OptionalFloat:
                            case EType.OptionalDouble:
                            case EType.OptionalInt32:
                            case EType.OptionalInt64:
                            case EType.OptionalSizeT:
                            case EType.OptionalString:
                            case EType.OptionalStringView:
                            case EType.OptionalChar:
                                yield return new IfPart(IfPart.EIfScope.If, $"{nav}.has_value()")
                                {
                                    success is null ? failure! : success
                                };
                                if (success is not null && failure is not null)
                                {
                                    yield return new IfPart(IfPart.EIfScope.Else, null)
                                    {
                                        failure
                                    };
                                };
                                yield break;
                        }
                    }
                }
                CaptureDefinition captureDefinition = captureDefinitions[i];
                CaptureDefinition? captureDefinitionLA = captureDefinitions.Length > i + 1 ? captureDefinitions[i + 1] : null;

                // Ensure this can be printed
                #region Safety Exist
                if (captureDefinition.Types.Count == 1)
                {
                    var type = captureDefinition.Types.First();
                    methodDefinition.AddRange(getWhitespaceGood(captureDefinition, type, false, new FullBody { }, new FullBody { $@"return;" }));
                }
                else
                {
                    methodDefinition.Add($@"switch (node{n}{captureDefinition.Name}.index())");
                    var switchScope = new ScopePart();
                    methodDefinition.Add(switchScope);
                    int index = 0;
                    foreach (var type in captureDefinition.Types)
                    {
                        switchScope.Add($"case {index++}:");
                        switchScope.AddRange(getWhitespaceGood(captureDefinition, type, true, new FullBody { }, new FullBody { $@"return;" }));
                        switchScope.Add("break;");
                    }
                }
                #endregion

                // Print out whitespace character stuff
                #region Whitespace Handling
                if (captureDefinitionLA is null)
                {
                    methodDefinition.Add($@"v.push_back({print_bs});");
                    methodDefinition.Add($@"v.push_back({print_ws});");
                    methodDefinition.Add($@"v.push_back({print_ws});");
                }
                else
                {
                    if (captureDefinitionLA.Types.Count == 1)
                    {
                        var type = captureDefinitionLA.Types.First();
                        methodDefinition.AddRange(getWhitespaceGood(captureDefinitionLA, type, false, new FullBody { $@"v.push_back({print_hr});" }, new FullBody { $@"v.push_back({print_bs});" }));
                    }
                    else
                    {
                        methodDefinition.Add($@"switch (node{n}{captureDefinitionLA.Name}.index())");
                        var switchScope = new ScopePart();
                        methodDefinition.Add(switchScope);
                        int index = 0;
                        foreach (var type in captureDefinitionLA.Types)
                        {
                            switchScope.Add($"case {index++}:");
                            switchScope.AddRange(getWhitespaceGood(captureDefinitionLA, type, true, new FullBody { $@"v.push_back({print_hr});" }, new FullBody { $@"v.push_back({print_bs});" }));
                            switchScope.Add("break;");
                        }
                    }

                    methodDefinition.Add($@"v.push_back({print_ws});");
                    methodDefinition.Add($@"v.push_back({print_ws});");
                }
                #endregion

                // Print out actual tree stuff
                #region Tree
                if (captureDefinition.Types.Count == 1)
                {
                    var type = captureDefinition.Types.First();
                    methodDefinition.AddRange(getPrintMethod(captureDefinition, type, false));
                }
                else
                {
                    methodDefinition.Add($@"switch (node{n}{captureDefinition.Name}.index())");
                    var switchScope = new ScopePart();
                    methodDefinition.Add(switchScope);
                    int index = 0;
                    foreach (var type in captureDefinition.Types)
                    {
                        switchScope.Add($"case {index++}:");
                        switchScope.AddRange(getPrintMethod(captureDefinition, type, true));
                        switchScope.Add("break;");
                    }
                }
                #endregion

                // Cleanup whitespace stuff
                methodDefinition.Add($@"v.pop_back();");
                methodDefinition.Add($@"v.pop_back();");
                methodDefinition.Add($@"v.pop_back();");
            }


            return methodDefinition;
        }
    }
}
