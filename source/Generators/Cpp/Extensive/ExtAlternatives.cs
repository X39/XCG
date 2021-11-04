using System.Linq;

namespace XCG.Generators.Cpp.Extensive
{
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
        /// <param name="cppOptions"></param>
        /// <param name="typeName">The type the <paramref name="alternatives"/> gets to capture things onto.</param>
        /// <returns></returns>
        public static MethodDefinition CreateMethodDefinition(this Parsing.Statements.Alternatives alternatives, CppOptions cppOptions, string typeName, string stateTypeName)
        {
            var ___localsCount = 0;
            string toUnique(string str) => string.Concat(str, (++___localsCount).ToString());
            var methodDefinition = new MethodDefinition(
                EType.Boolean,
                cppOptions.ToUnique(string.Concat(cppOptions.MethodsPrefix, "alternatives")),
                new ArgImpl { Name = Constants.isCanVariable, Type = EType.Boolean },
                new ArgImpl { Name = Constants.classInstanceVariable, TypeString = typeName, ReferenceCount = 1 },
                new ArgImpl { Name = Constants.stateInstanceVariable, TypeString = stateTypeName, ReferenceCount = 1 },
                new ArgImpl { Name = Constants.depthVariable, Type = EType.SizeT }
            );
            // Unique Variables
            var resettable = toUnique("resettable");



            var matches = alternatives.Matches.ToArray();


            methodDefinition.Add(new FullBody
            {
                $@"resettable {resettable}(*this);",
            });
            var isFirst = true;
            foreach (var match in matches)
            {
                methodDefinition.Add(new IfPart(isFirst, $@"{cppOptions.FromCache(match).Name}(true, {Constants.classInstanceVariable}, {Constants.stateInstanceVariable}, {Constants.depthVariable} + 1)")
                {
                    new IfPart(IfPart.EIfScope.If, Constants.isCanVariable)
                    {
                        new DebugPart { $@"trace(""Returning true on {methodDefinition.Name}"", {Constants.depthVariable});" },
                        new ReturnPart(EValueConstant.True)
                    },
                    new IfPart(IfPart.EIfScope.Else, null)
                    {
                        $@"{resettable}.reset();",
                        $@"{cppOptions.FromCache(match).Name}(false, {Constants.classInstanceVariable}, {Constants.stateInstanceVariable}, {Constants.depthVariable} + 1);",
                        new DebugPart { $@"trace(""Returning true on {methodDefinition.Name}"", {Constants.depthVariable});" },
                        new ReturnPart(EValueConstant.True)
                    }
                });
                isFirst = false;
            }
            if (alternatives.CatchesErrors)
            {
                methodDefinition.Add(new IfPart(IfPart.EIfScope.Else, $@"!{Constants.isCanVariable}")
                {
                    $@"report(""Failed to match one of the following: {{ {string.Join(", ", matches.SelectMany((q) => q.Matches.OfType<Parsing.Reference>()).Select((q) => q.Text))} }}"", {Constants.depthVariable});",
                });
            }
            methodDefinition.Add($@"{resettable}.reset();");
            methodDefinition.Add(new DebugPart { $@"trace(""Returning false on {methodDefinition.Name}"", {Constants.depthVariable});" });
            methodDefinition.Add(new ReturnPart(EValueConstant.False));
            return methodDefinition;
        }
    }
}
