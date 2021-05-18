using System;

namespace XCG.Generators.Cpp.Extensive
{
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
        /// <param name="skip">The amount of match-tokens to skip.</param>
        /// <param name="typeName">The type the <paramref name="while"/> gets to capture things onto.</param>
        /// <returns></returns>
        public static MethodDefinition CreateMethodDefinition(this Parsing.Statements.While @while, CppOptions cppOptions, string typeName, string stateTypeName)
        {
            int ___localsCount = 0;
            string toUnique(string str) => String.Concat(str, (++___localsCount).ToString());
            string? resetable = toUnique("resetable");
            string? resetable_condition = toUnique("resetable");

            var whileName = cppOptions.ToUnique("while");
            var methodDefinition = new MethodDefinition(
                EType.Boolean,
                cppOptions.ToUnique(String.Concat(cppOptions.MethodsPrefix, whileName, "_")),
                new ArgImpl { Name = Constants.isCanVariable, Type = EType.Boolean },
                new ArgImpl { Name = Constants.classInstanceVariable, TypeString = typeName, ReferenceCount = 1 },
                new ArgImpl { Name = Constants.stateInstanceVariable, TypeString = stateTypeName, ReferenceCount = 1 },
                new ArgImpl { Name = Constants.depthVariable, Type = EType.SizeT }
            )
            {
                $@"resetable {resetable}(*this);"
            };

            var conditionVariable = toUnique("cond");
            var effectiveCondition = String.Concat(@while.Negated ? $"!{conditionVariable}" : conditionVariable, " && current() != '\\0'");
            methodDefinition.AddRange(@while.Condition!.GetEvaluationResult(cppOptions, stateTypeName, conditionVariable, true));
            methodDefinition.Add($@"{resetable}.reset();");
            foreach (var isCan in Constants.TrueFalseArray)
            {
                var isCanIf = isCan ? new IfPart(IfPart.EIfScope.If, Constants.isCanVariable) : new IfPart(IfPart.EIfScope.Else, null);
                methodDefinition.Add(isCanIf);

                // Create while loop
                var whilePart = new WhilePart(effectiveCondition);
                isCanIf.Add(whilePart);

                // Handle any following statement
                whilePart.AddRange(@while.Children.Handle(cppOptions, isCan, toUnique));

                // and re-evaluate the while condition
                whilePart.Add($@"resetable {resetable_condition}(*this);");
                whilePart.AddRange(@while.Condition!.GetEvaluationResult(cppOptions, stateTypeName, conditionVariable, false));
                whilePart.Add($@"{resetable_condition}.reset();");

                // finally return true
                isCanIf.Add(new DebugPart { $@"trace(""Returning true on {methodDefinition.Name}"", {Constants.depthVariable});" });
                isCanIf.Add(new ReturnPart(EValueConstant.True));
            }
            return methodDefinition;
        }
    }
}
