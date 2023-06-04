using System.Collections.Generic;
using System.Collections.Immutable;
using System.Linq;
using X39.Systems.XCG.Generators.Base.Contracts;
using X39.Systems.XCG.Generators.Base.Expressions;
using X39.Util;

namespace X39.Systems.XCG.Generators.Base.Statements;

public class CaseCodeStatement : CodeStatementHostBase
{
    public IReadOnlyCollection<ValueExpression> Values { get; }

    public CaseCodeStatement(ICodeStatementsHost parent, IEnumerable<ValueExpression> caseValues) : base(parent)
    {
        Values = caseValues.ToImmutableArray();
    }

    public CaseCodeStatement(ICodeStatementsHost parent, ValueExpression caseValue1,
        params ValueExpression[] caseValueN)
        : this(parent, caseValueN.Prepend(caseValue1))
    {
    }

    public CaseCodeStatement(ICodeStatementsHost parent, ValueExpression caseValue)
        : this(parent, caseValue.MakeEnumerable())
    {
    }
}