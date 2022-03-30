﻿using System.Linq;
using XCG.Generators.CSharp.CodeGeneration;

namespace XCG.Generators.CSharp.CstParsing;

internal static class ExtAlternatives
{
    /// <summary>
    /// Creates the <see cref="MethodDefinition"/> for a provided <paramref name="alternatives"/>.
    /// </summary>
    /// <remarks>
    /// Alternatives Methods always are of the following prototype:
    /// <code>bool function(bool is_can, type actual)</code>
    /// where <code>function</code> is the name of the alternatives function and <code>type</code> is the calling structure type.
    /// </remarks>
    /// <param name="alternatives"></param>
    /// <param name="cSharpOptions"></param>
    /// <param name="typeName">The type the <paramref name="alternatives"/> gets to capture things onto.</param>
    /// <param name="stateTypeName"></param>
    /// <returns></returns>
    public static MethodDefinition CreateMethodDefinition(this Parsing.Statements.Alternatives alternatives, CSharpOptions cSharpOptions, string typeName, string stateTypeName)
    {
        var localsCount = 0;
        string ToUnique(string str) => string.Concat(str, (++localsCount).ToString());
        var methodDefinition = new MethodDefinition(
            EType.Boolean,
            cSharpOptions.ToUnique(string.Concat(cSharpOptions.MethodsPrefix, "alternatives")),
            new ArgImpl { Name = Constants.IsCanVariable, Type = EType.Boolean },
            new ArgImpl { Name = Constants.ClassInstanceVariable, TypeString = typeName },
            new ArgImpl { Name = Constants.StateInstanceVariable, TypeString = stateTypeName },
            new ArgImpl { Name = Constants.DepthVariable, Type = EType.SizeT }
        );
        // Unique Variables
        var resettable = ToUnique("resettable");



        var matches = alternatives.Matches.ToArray();


        methodDefinition.Add(new FullBody
        {
            $@"resettable {resettable}(*this);",
        });
        var isFirst = true;
        foreach (var match in matches)
        {
            methodDefinition.Add(new IfPart(isFirst, $@"{cSharpOptions.FromCache(match).Name}(true, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1)")
            {
                new IfPart(IfPart.EIfScope.If, Constants.IsCanVariable)
                {
                    new DebugPart { $@"trace(""Returning true on {methodDefinition.Name}"", {Constants.DepthVariable});" },
                    new ReturnPart(EValueConstant.True)
                },
                new IfPart(IfPart.EIfScope.Else, null)
                {
                    $@"{resettable}.reset();",
                    $@"{cSharpOptions.FromCache(match).Name}(false, {Constants.ClassInstanceVariable}, {Constants.StateInstanceVariable}, {Constants.DepthVariable} + 1);",
                    new DebugPart { $@"trace(""Returning true on {methodDefinition.Name}"", {Constants.DepthVariable});" },
                    new ReturnPart(EValueConstant.True)
                }
            });
            isFirst = false;
        }
        if (alternatives.CatchesErrors)
        {
            methodDefinition.Add(new IfPart(IfPart.EIfScope.Else, $@"!{Constants.IsCanVariable}")
            {
                $@"report(""Failed to match one of the following: {{ {string.Join(", ", matches.SelectMany((q) => q.Matches.OfType<Parsing.Reference>()).Select((q) => q.Text))} }}"", {Constants.DepthVariable});",
            });
        }
        methodDefinition.Add($@"{resettable}.reset();");
        methodDefinition.Add(new DebugPart { $@"trace(""Returning false on {methodDefinition.Name}"", {Constants.DepthVariable});" });
        methodDefinition.Add(new ReturnPart(EValueConstant.False));
        return methodDefinition;
    }
}