using System;
using System.Linq;

namespace XCG.Generators.Cpp.Extensive
{
    internal static class ExtIf
    {
        /// <summary>
        /// Creates the <see cref="MethodDefinition"/> for a provided <paramref name="if"/>.
        /// </summary>
        /// <remarks>
        /// While Methods always are of the following prototype:
        /// <code>bool function(bool is_can, type actual)</code>
        /// where <code>function</code> is the name of the match function and <code>type</code> is the calling structure type.
        /// </remarks>
        /// <param name="if"></param>
        /// <param name="cppOptions"></param>
        /// <param name="skip">The amount of match-tokens to skip.</param>
        /// <param name="typeName">The type the <paramref name="if"/> gets to capture things onto.</param>
        /// <returns></returns>
        public static MethodDefinition CreateMethodDefinition(this Parsing.Statements.If @if, CppOptions cppOptions, string typeName, string stateTypeName)
        {
            int ___localsCount = 0;
            string toUnique(string str) => String.Concat(str, (++___localsCount).ToString());
            string? resetable = toUnique("resetable");

            var ifName = cppOptions.ToUnique("if");
            var methodDefinition = new MethodDefinition(
                EType.Boolean,
                cppOptions.ToUnique(String.Concat(cppOptions.MethodsPrefix, ifName, "_")),
                new ArgImpl { Name = Constants.isCanVariable, Type = EType.Boolean },
                new ArgImpl { Name = Constants.classInstanceVariable, TypeString = typeName, ReferenceCount = 1 },
                new ArgImpl { Name = Constants.stateInstanceVariable, TypeString = stateTypeName, ReferenceCount = 1 }
            )
            {
                $@"resetable {resetable}(*this);"
            };


            var conditionVariable = toUnique("cond");
            methodDefinition.AddRange(@if.Condition!.GetEvaluationResult(cppOptions, conditionVariable, true));
            methodDefinition.Add($@"{resetable}.reset();");


            foreach (var isCan in Constants.TrueFalseArray)
            {
                var isCanIf = isCan ? new IfPart(IfPart.EIfScope.If, Constants.isCanVariable) : new IfPart(IfPart.EIfScope.Else, null);
                methodDefinition.Add(isCanIf);


                var ifPart = new IfPart(IfPart.EIfScope.If, @if.Negated ? $"!{conditionVariable}" : conditionVariable);
                isCanIf.Add(ifPart);
                // Handle any if statements
                ifPart.AddRange(@if.Statements.Handle(cppOptions, isCan, toUnique));
                ifPart.Add(new ReturnPart(EValueConstant.True));


                if (@if.Else.Any())
                {
                    var elsePart = new IfPart(IfPart.EIfScope.Else, null);
                    isCanIf.Add(elsePart);

                    // Handle any else statements
                    elsePart.AddRange(@if.Else.Handle(cppOptions, isCan, toUnique));
                    elsePart.Add(new ReturnPart(EValueConstant.True));
                }
                else
                {
                    // Handle any else statements
                    isCanIf.Add(new ReturnPart(EValueConstant.False));
                }
            }
            return methodDefinition;
        }
    }
}
