using System.Collections.Generic;

namespace X39.Systems.XCG.Generators.Base.Contracts;

public interface ICodeStatementsHost : ICodeStatement, IList<ICodeStatement>
{
}
