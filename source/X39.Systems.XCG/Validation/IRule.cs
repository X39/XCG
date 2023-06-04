using System.Collections.Generic;

namespace X39.Systems.XCG.Validation;

public interface IRule
{
    /// <summary>
    /// The realm this rule lives in.
    /// It is recommended to use Single-Character realms.
    /// </summary>
    string Realm { get; }

    /// <summary>
    /// The code this rule holds.
    /// Code should always be positive.
    /// </summary>
    int Code { get; }

    /// <summary>
    /// The severity of this rule.
    /// If the severity of a given Rule is <see cref="ESeverity.Error"/> and
    /// <see cref="IsValid(Parsing.Parser)"/> evaluates to any <see cref="Hint"/>,
    /// the generation of code is aborted.
    /// </summary>
    ESeverity Severity { get; }

    /// <summary>
    /// Method, validating whether this rule passes or not.
    /// If this returns false, the rule is assumed to have not passed and gets raised
    /// to the user.
    /// See <see cref="Severity"/> for further infos.
    /// </summary>
    /// <param name="parser">The whole parser instance.</param>
    /// <returns>A range of <see cref="Hint"/> structures describing
    /// the different things encountered by this <see cref="IRule"/>.</returns>
    IEnumerable<Hint> IsValid(Parsing.Parser parser);
}