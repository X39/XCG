using XCG.Generators.Cpp.CodeGeneration;

namespace XCG.Generators.Cpp.CstParsing;

internal static class ExtWhile
{
    /// <summary>
    /// Creates the <see cref="MethodDefinition"/> for a provided <paramref name="while"/>.
    /// </summary>
    /// <remarks>
    /// While Methods always are of the following prototype:
    /// <code>bool function(bool is_can, type actual)</code>
    /// where <code>function</code> is the name of the match function and <code>type</code> is the calling structure type.
    /// </remarks>
    /// <param name="while"></param>
    /// <param name="cppOptions"></param>
    /// <param name="typeName">The type the <paramref name="while"/> gets to capture things onto.</param>
    /// <param name="stateTypeName"></param>
    /// <returns></returns>
    public static MethodDefinition CreateMethodDefinition(this Parsing.Statements.While @while,
        CppOptions cppOptions, string typeName, string stateTypeName)
    {
        var localsCount = 0;
        string ToUnique(string str) => string.Concat(str, (++localsCount).ToString());
        var resettable = ToUnique("resettable");
        var resettableCondition = ToUnique("resettable");

        var whileName = cppOptions.ToUnique("while");
        var methodDefinition = new MethodDefinition(
            EType.Boolean,
            cppOptions.ToUnique(string.Concat(cppOptions.MethodsPrefix, whileName, "_")),
            new ArgImpl {Name = Constants.IsCanVariable, Type = EType.Boolean},
            new ArgImpl {Name = Constants.ClassInstanceVariable, TypeString = typeName, ReferenceCount = 1},
            new ArgImpl {Name = Constants.StateInstanceVariable, TypeString = stateTypeName, ReferenceCount = 1},
            new ArgImpl {Name = Constants.DepthVariable, Type = EType.SizeT}
        )
        {
            $@"resettable {resettable}(*this);"
        };

        var conditionVariable = ToUnique("cond");
        var effectiveCondition = string.Concat(@while.Negated ? $"!{conditionVariable}" : conditionVariable,
            " && current() != '\\0'");
        methodDefinition.AddRange(@while.Condition!.GetEvaluationResult(cppOptions, stateTypeName,
            conditionVariable, true, ToUnique));
        methodDefinition.Add($@"{resettable}.reset();");
        foreach (var isCan in Constants.TrueFalseArray)
        {
            var isCanIf = isCan
                ? new IfPart(IfPart.EIfScope.If, Constants.IsCanVariable)
                : new IfPart(IfPart.EIfScope.Else, null);
            methodDefinition.Add(isCanIf);

            // Create while loop
            var whilePart = new WhilePart(effectiveCondition);
            isCanIf.Add(whilePart);

            // Handle any following statement
            whilePart.AddRange(@while.Children.Handle(cppOptions, isCan, ToUnique));

            // and re-evaluate the while condition
            whilePart.Add($@"resettable {resettableCondition}(*this);");
            whilePart.AddRange(@while.Condition!.GetEvaluationResult(cppOptions, stateTypeName, conditionVariable,
                false, ToUnique));
            whilePart.Add($@"{resettableCondition}.reset();");

            // finally return true
            isCanIf.Add(new DebugPart
                {$@"trace(""Returning true on {methodDefinition.Name}"", {Constants.DepthVariable});"});
            isCanIf.Add(new ReturnPart(EValueConstant.True));
        }

        return methodDefinition;
    }
}