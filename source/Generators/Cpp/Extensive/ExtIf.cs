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
        /// <param name="typeName">The type the <paramref name="if"/> gets to capture things onto.</param>
        /// <param name="stateTypeName"></param>
        /// <returns></returns>
        public static MethodDefinition CreateMethodDefinition(this Parsing.Statements.If @if, CppOptions cppOptions, string typeName, string stateTypeName)
        {
            var localsCount = 0;
            string ToUnique(string str) => string.Concat(str, (++localsCount).ToString());
            var resettable = ToUnique("resettable");

            var ifName = cppOptions.ToUnique("if");
            var methodDefinition = new MethodDefinition(
                EType.Boolean,
                cppOptions.ToUnique(string.Concat(cppOptions.MethodsPrefix, ifName, "_")),
                new ArgImpl { Name = Constants.IsCanVariable, Type = EType.Boolean },
                new ArgImpl { Name = Constants.ClassInstanceVariable, TypeString = typeName, ReferenceCount = 1 },
                new ArgImpl { Name = Constants.StateInstanceVariable, TypeString = stateTypeName, ReferenceCount = 1 },
                new ArgImpl { Name = Constants.DepthVariable, Type = EType.SizeT }
            )
            {
                $@"resettable {resettable}(*this);"
            };


            var conditionVariable = ToUnique("cond");
            methodDefinition.AddRange(@if.Condition!.GetEvaluationResult(cppOptions, stateTypeName, conditionVariable, true, ToUnique));
            methodDefinition.Add($@"{resettable}.reset();");


            foreach (var isCan in Constants.TrueFalseArray)
            {
                var isCanIf = isCan ? new IfPart(IfPart.EIfScope.If, Constants.IsCanVariable) : new IfPart(IfPart.EIfScope.Else, null);
                methodDefinition.Add(isCanIf);


                var ifPart = new IfPart(IfPart.EIfScope.If, @if.Negated ? $"!{conditionVariable}" : conditionVariable);
                isCanIf.Add(ifPart);
                // Handle any if statements
                ifPart.AddRange(@if.Children.Handle(cppOptions, isCan, ToUnique));
                ifPart.Add(new DebugPart { $@"trace(""Returning true on {methodDefinition.Name}"", {Constants.DepthVariable});" });
                ifPart.Add(new ReturnPart(EValueConstant.True));


                if (@if.Else.Any())
                {
                    var elsePart = new IfPart(IfPart.EIfScope.Else, null);
                    isCanIf.Add(elsePart);

                    // Handle any else statements
                    elsePart.AddRange(@if.Else.Handle(cppOptions, isCan, ToUnique));
                    elsePart.Add(new DebugPart { $@"trace(""Returning true on {methodDefinition.Name}"", {Constants.DepthVariable});" });
                    elsePart.Add(new ReturnPart(EValueConstant.True));
                }
                else
                {
                    // Handle any else statements
                    isCanIf.Add(new DebugPart { $@"trace(""Returning true on {methodDefinition.Name}"", {Constants.DepthVariable});" });
                    isCanIf.Add(new ReturnPart(EValueConstant.True));
                }
            }
            return methodDefinition;
        }
    }
}
