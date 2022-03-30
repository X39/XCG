using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace XCG.Generators.CSharp.CodeGeneration;

internal class ClassDefinition : ICSharpPart, IHasName
{
    public string? BaseName { get; set; }
    public string Name { get; }
    public string FullName => BaseName is null ? Name : string.Concat(BaseName, "::", Name);
    public List<ICSharpPart> PrivateParts { get; init; }
    public List<ICSharpPart> ProtectedParts { get; init; }
    public List<ICSharpPart> PublicParts { get; init; }
    public ClassDefinition(string name)
    {
        Name = name;
        PrivateParts = new List<ICSharpPart>();
        ProtectedParts = new List<ICSharpPart>();
        PublicParts = new List<ICSharpPart>();
    }

    public void WriteImplementation(CSharpOptions options, StreamWriter writer, string whitespace)
    {
        foreach (var generatorPart in PrivateParts)
        {
            generatorPart.BaseName = FullName;
            generatorPart.WriteImplementation(options, writer, whitespace);
        }

        foreach (var generatorPart in ProtectedParts)
        {
            generatorPart.BaseName = FullName;
            generatorPart.WriteImplementation(options, writer, whitespace);
        }

        foreach (var generatorPart in PublicParts)
        {
            generatorPart.BaseName = FullName;
            generatorPart.WriteImplementation(options, writer, whitespace);
        }
    }


    public MethodDefinition CreateVisitTreeMethodDefinition(CSharpOptions cSharpOptions)
    {
        var methodDefinition = new MethodDefinition(
            "bool", string.Concat(cSharpOptions.MethodsPrefix, "visit"),
            new ArgImpl { Name = "node", TypeString = FullName })
        {
            $@"if (!visit_enter(node)) {{ return false; }}",
        };

        var captureDefinitions = PublicParts.Concat(ProtectedParts).Concat(PrivateParts).WhereIs<CaptureDefinition>().ToArray();
        foreach (var t in captureDefinitions)
        {
            void HandleSingle(ICSharpContainerBase container, TypeImpl type, string nav)
            {
                if (type.TypeString is not null)
                {
                    container.Add(new IfPart(IfPart.EIfScope.If, nav)
                    {
                        new VariableDefinition(EType.Var, "lines", $@"{string.Concat(cSharpOptions.MethodsPrefix, "visit")}({nav})"),
                    });
                }
            }
            void Handle(CaptureDefinition def, ICSharpContainerBase container, string nav)
            {
                if (def.Types.Count == 1)
                {
                    var type = def.Types.First();
                    HandleSingle(container, type, nav);
                }
                else
                {
                    //var nav = captureDefinition.IsSingleHit ? $"node{n}{captureDefinition.Name}" : iteratorName;
                    container.Add($@"switch ({nav}.index())");
                    var scope = new ScopePart();
                    container.Add(scope);

                    for (var typeIndex = 0; typeIndex < def.Types.Count; typeIndex++)
                    {
                        var type = def.Types[typeIndex];
                        scope.Add($@"case {typeIndex}:");
                        HandleSingle(scope, type, $@"std::get<{type.ToString(cSharpOptions)}>({nav})");
                        scope.Add($@"break;");
                    }
                }
            }

            if (t.IsSingleHit)
            {
                var nav = $"node->{t.Name}";
                Handle(t, methodDefinition, nav);
            }
            else
            {
                var nav = $"element";
                methodDefinition.Add($@"for (auto element : node->{t.Name})");
                var scope = new ScopePart();
                methodDefinition.Add(scope);
                Handle(t, scope, nav);
            }
        }

        methodDefinition.Add(new ReturnPart("visit_leave(node)"));
        return methodDefinition;
    }
    public MethodDefinition CreatePrintTreeMethodDefinition(CSharpOptions cSharpOptions)
    {
        var level     = $@"std::string(""{new string(' ', cSharpOptions.CreateStringTreeSpaces)}  "")";
        var levelAlt = $@"std::string(""{new string(' ', cSharpOptions.CreateStringTreeSpaces)}- "")";
        var methodDefinition = new MethodDefinition(
            "List<std::string>", string.Concat(cSharpOptions.MethodsPrefix, "create_string_tree"),
            new ArgImpl { Name = "node", TypeString = FullName },
            new ArgImpl { Name = "contents", Type = EType.StringView })
        {
            new VariableDefinition("List<std::string>", "output"),
            $@"output.push_back(""{Name}:"");",
        };

        var captureNameColoringStart = !cSharpOptions.ConsoleColorCaptureName ? string.Empty : string.Concat("\"", TerminalColor.ForegroundBrightBlack, "\"");
        var captureNameColoringEnd = !cSharpOptions.ConsoleColorCaptureName ? string.Empty : string.Concat("\"", TerminalColor.Reset, "\"");

        var captureDefinitions = PublicParts.Concat(ProtectedParts).Concat(PrivateParts).WhereIs<CaptureDefinition>().ToArray();
        foreach (var t in captureDefinitions)
        {
            void HandleSingle(ICSharpContainerBase container, TypeImpl type, string nav, string captureName)
            {
                if (type.TypeString is not null)
                {
                    container.Add(new IfPart(IfPart.EIfScope.If, nav)
                    {
                        new VariableDefinition(EType.Var, "lines", $@"{string.Concat(cSharpOptions.MethodsPrefix, "create_string_tree")}({nav}, contents)"),
                        $@"bool first = true;",
                        $@"for (auto line : lines)",
                        new ScopePart
                        {
                            $@"output.push_back((first ? {levelAlt} : {level}) + (first ? line + {captureNameColoringStart} "" [{captureName}]"" {captureNameColoringEnd} : line));",
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
            void Handle(CaptureDefinition def, ICSharpContainerBase container, string nav, string captureName)
            {
                if (def.Types.Count == 1)
                {
                    var type = def.Types.First();
                    HandleSingle(container, type, nav, captureName);
                }
                else
                {
                    //var nav = captureDefinition.IsSingleHit ? $"node{n}{captureDefinition.Name}" : iteratorName;
                    container.Add($@"switch ({nav}.index())");
                    var scope = new ScopePart();
                    container.Add(scope);

                    for (var typeIndex = 0; typeIndex < def.Types.Count; typeIndex++)
                    {
                        var type = def.Types[typeIndex];
                        scope.Add($@"case {typeIndex}:");
                        HandleSingle(scope, type, $@"std::get<{type.ToString(cSharpOptions)}>({nav})", captureName);
                        scope.Add($@"break;");
                    }
                }
            }
            var captureDefinition = t;

            if (captureDefinition.IsSingleHit)
            {
                var nav = $"node->{captureDefinition.Name}";
                Handle(captureDefinition, methodDefinition, nav, captureDefinition.Name);
            }
            else
            {
                var nav = $"element";
                methodDefinition.Add($@"for (auto element : node->{captureDefinition.Name})");
                var scope = new ScopePart();
                methodDefinition.Add(scope);
                Handle(captureDefinition, scope, nav, captureDefinition.Name);
            }
        }

        methodDefinition.Add(new ReturnPart("output"));
        return methodDefinition;
    }
}