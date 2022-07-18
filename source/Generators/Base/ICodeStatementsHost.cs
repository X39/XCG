using System.Collections.Generic;

namespace XCG.Generators.Base;

public interface ICodeStatementsHost : ICodeStatement, IList<ICodeStatement>
{
}
