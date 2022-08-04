using System.Collections.Generic;

namespace XCG.Generators.Base.Contracts;

public interface ICodeStatementsHost : ICodeStatement, IList<ICodeStatement>
{
}
