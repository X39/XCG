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

            var whileName = cppOptions.ToUnique("while");
            var methodDefinition = new MethodDefinition(
                EType.Boolean,
                cppOptions.ToUnique(String.Concat(cppOptions.MethodsPrefix, whileName, "_")),
                new ArgImpl { Name = Constants.isCanVariable, Type = EType.Boolean },
                new ArgImpl { Name = Constants.classInstanceVariable, TypeString = typeName, ReferenceCount = 1 },
                new ArgImpl { Name = Constants.stateInstanceVariable, TypeString = stateTypeName, ReferenceCount = 1 }
            )
            {
                $@"resetable {resetable}(*this);"
            };

            var conditionVariable = toUnique("cond");
            methodDefinition.AddRange(@while.Condition!.GetEvaluationResult(cppOptions, conditionVariable));
            #region IsCan
            var isCanIf = new IfPart(IfPart.EIfScope.If, Constants.isCanVariable);
            methodDefinition.Add(isCanIf);

            // Create while loop
            var whilePart = new WhilePart(@while.Negated ? $"!{conditionVariable}" : conditionVariable);
            isCanIf.Add(whilePart);

            // Handle any following statement
            whilePart.AddRange(@while.Statements.Handle(cppOptions, true, toUnique));

            // and re-evaluate the while condition
            whilePart.AddRange(@while.Condition!.GetEvaluationResult(cppOptions, conditionVariable));

            // finally return true
            isCanIf.Add(new ReturnPart(EValueConstant.True));
            #endregion
            #region IsNotCan
            // Create Else
            var isNotCanif = new IfPart(IfPart.EIfScope.Else, null);
            methodDefinition.Add(isNotCanif);

            // Create while loop
            whilePart = new WhilePart(@while.Negated ? $"!{conditionVariable}" : conditionVariable);
            isNotCanif.Add(whilePart);

            // Handle any following statement
            whilePart.AddRange(@while.Statements.Handle(cppOptions, false, toUnique));

            // and re-evaluate the while condition
            whilePart.AddRange(@while.Condition!.GetEvaluationResult(cppOptions, conditionVariable));

            // finally return true
            isNotCanif.Add(new ReturnPart(EValueConstant.True));
            #endregion
            return methodDefinition;
        }
    }
}
