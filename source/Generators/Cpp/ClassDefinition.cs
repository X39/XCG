using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using XCG.Generators.Cpp.Extensive;

namespace XCG.Generators.Cpp
{
    internal class ClassDefinition : ICppPart, IHasName
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


        public MethodDefinition CreateVisitTreeMethodDefinition(CppOptions cppOptions)
        {
            string level = $@"std::string(""{new string(' ', cppOptions.CreateStringTreeSpaces)}  "")";
            string level_alt = $@"std::string(""{new string(' ', cppOptions.CreateStringTreeSpaces)}- "")";
            var methodDefinition = new MethodDefinition(
                "bool", String.Concat(cppOptions.MethodsPrefix, "visit"),
                new ArgImpl { Name = "node", TypeString = this.FullName.ToCppSharedPtrType() })
            {
                $@"if (!visit_enter(node)) {{ return false; }}",
            };

            var captureNameColoringStart = !cppOptions.ConsoleColorCaptureName ? string.Empty : string.Concat("\"", TerminalColor.ForegroundBrightBlack, "\"");
            var captureNameColoringEnd = !cppOptions.ConsoleColorCaptureName ? string.Empty : string.Concat("\"", TerminalColor.Reset, "\"");

            CaptureDefinition[] captureDefinitions = this.PublicParts.Concat(this.ProtectedParts).Concat(this.PrivateParts).WhereIs<CaptureDefinition>().ToArray();
            for (int i = 0; i < captureDefinitions.Length; i++)
            {
                void handleSingle(CppContainerBase container, TypeImpl type, string nav, string captureName)
                {
                    if (type.TypeString is not null)
                    {
                        container.Add(new IfPart(IfPart.EIfScope.If, nav)
                        {
                            new VariableDefinition(EType.Auto, "lines", $@"{String.Concat(cppOptions.MethodsPrefix, "visit")}({nav})"),
                        });
                    }
                }
                void handle(CaptureDefinition def, CppContainerBase container, string nav, string captureName)
                {
                    if (def.Types.Count == 1)
                    {
                        var type = def.Types.First();
                        handleSingle(container, type, nav, captureName);
                    }
                    else
                    {
                        //var nav = captureDefinition.IsSingleHit ? $"node{n}{captureDefinition.Name}" : iteratorName;
                        container.Add($@"switch ({nav}.index())");
                        var scope = new ScopePart();
                        container.Add(scope);

                        for (int typeIndex = 0; typeIndex < def.Types.Count; typeIndex++)
                        {
                            var type = def.Types[typeIndex];
                            scope.Add($@"case {typeIndex}:");
                            handleSingle(scope, type, $@"std::get<{type.ToString(cppOptions)}>({nav})", captureName);
                            scope.Add($@"break;");
                        }
                    }
                }
                var captureDefinition = captureDefinitions[i];

                if (captureDefinition.IsSingleHit)
                {
                    var nav = $"node->{captureDefinition.Name}";
                    handle(captureDefinition, methodDefinition, nav, captureDefinition.Name);
                }
                else
                {
                    var nav = $"element";
                    methodDefinition.Add($@"for (auto element : node->{captureDefinition.Name})");
                    var scope = new ScopePart();
                    methodDefinition.Add(scope);
                    handle(captureDefinition, scope, nav, captureDefinition.Name);
                }
            }

            methodDefinition.Add(new ReturnPart("visit_leave(node)"));
            return methodDefinition;
        }
        public MethodDefinition CreatePrintTreeMethodDefinition(CppOptions cppOptions)
        {
            string level     = $@"std::string(""{new string(' ', cppOptions.CreateStringTreeSpaces)}  "")";
            string level_alt = $@"std::string(""{new string(' ', cppOptions.CreateStringTreeSpaces)}- "")";
            var methodDefinition = new MethodDefinition(
                "std::vector<std::string>", String.Concat(cppOptions.MethodsPrefix, "create_string_tree"),
                new ArgImpl { Name = "node", TypeString = this.FullName.ToCppSharedPtrType() },
                new ArgImpl { Name = "contents", Type = EType.StringView })
            {
                new VariableDefinition("std::vector<std::string>", "output"),
                $@"output.push_back(""{this.Name}:"");",
            };

            var captureNameColoringStart = !cppOptions.ConsoleColorCaptureName ? string.Empty : string.Concat("\"", TerminalColor.ForegroundBrightBlack, "\"");
            var captureNameColoringEnd = !cppOptions.ConsoleColorCaptureName ? string.Empty : string.Concat("\"", TerminalColor.Reset, "\"");

            CaptureDefinition[] captureDefinitions = this.PublicParts.Concat(this.ProtectedParts).Concat(this.PrivateParts).WhereIs<CaptureDefinition>().ToArray();
            for (int i = 0; i < captureDefinitions.Length; i++)
            {
                void handleSingle(CppContainerBase container, TypeImpl type, string nav, string captureName)
                {
                    if (type.TypeString is not null)
                    {
                        container.Add(new IfPart(IfPart.EIfScope.If, nav)
                        {
                            new VariableDefinition(EType.Auto, "lines", $@"{String.Concat(cppOptions.MethodsPrefix, "create_string_tree")}({nav}, contents)"),
                            $@"bool first = true;",
                            $@"for (auto line : lines)",
                            new ScopePart
                            {
                                $@"output.push_back((first ? {level_alt} : {level}) + (first ? line + {captureNameColoringStart} "" [{captureName}]"" {captureNameColoringEnd} : line));",
                                $@"first = false;",
                            }
                        });
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
                                container.Add($@"output.push_back({level} + std::to_string({nav}));");
                                break;

                            case EType.OptionalBoolean:
                            case EType.OptionalFloat:
                            case EType.OptionalDouble:
                            case EType.OptionalInt32:
                            case EType.OptionalInt64:
                            case EType.OptionalSizeT:
                                container.Add(new IfPart(IfPart.EIfScope.If, $@"{nav}.has_value()")
                                {
                                    $@"output.push_back({level} + std::to_string({nav}.value()));"
                                });
                                break;

                            case EType.String:
                            case EType.StringView:
                            case EType.Char:
                                container.Add($@"output.push_back({level} + ""`"" + {nav} + ""`"");");
                                break;

                            case EType.OptionalString:
                            case EType.OptionalStringView:
                            case EType.OptionalChar:
                                container.Add(new IfPart(IfPart.EIfScope.If, $@"{nav}.has_value()")
                                {
                                    $@"output.push_back({level} + ""`"" + {nav}.value() + ""`"");"
                                });
                                break;

                            case EType.Token:
                                container.Add($@"output.push_back({level} + ""token (L"" + std::to_string({nav}.line) + ""; C"" + std::to_string({nav}.column) + ""; O"" + std::to_string({nav}.offset) + "") `"" + std::string(contents.substr({nav}.offset, {nav}.length).begin(), contents.substr({nav}.offset, {nav}.length).end()) + ""`"");");
                                break;
                        }
                    }
                }
                void handle(CaptureDefinition def, CppContainerBase container, string nav, string captureName)
                {
                    if (def.Types.Count == 1)
                    {
                        var type = def.Types.First();
                        handleSingle(container, type, nav, captureName);
                    }
                    else
                    {
                        //var nav = captureDefinition.IsSingleHit ? $"node{n}{captureDefinition.Name}" : iteratorName;
                        container.Add($@"switch ({nav}.index())");
                        var scope = new ScopePart();
                        container.Add(scope);

                        for (int typeIndex = 0; typeIndex < def.Types.Count; typeIndex++)
                        {
                            var type = def.Types[typeIndex];
                            scope.Add($@"case {typeIndex}:");
                            handleSingle(scope, type, $@"std::get<{type.ToString(cppOptions)}>({nav})", captureName);
                            scope.Add($@"break;");
                        }
                    }
                }
                var captureDefinition = captureDefinitions[i];

                if (captureDefinition.IsSingleHit)
                {
                    var nav = $"node->{captureDefinition.Name}";
                    handle(captureDefinition, methodDefinition, nav, captureDefinition.Name);
                }
                else
                {
                    var nav = $"element";
                    methodDefinition.Add($@"for (auto element : node->{captureDefinition.Name})");
                    var scope = new ScopePart();
                    methodDefinition.Add(scope);
                    handle(captureDefinition, scope, nav, captureDefinition.Name);
                }
            }

            methodDefinition.Add(new ReturnPart("output"));
            return methodDefinition;
        }
    }
}
