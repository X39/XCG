using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;
using XCG.Parsing;
using XCG.Validation;

namespace XCG;

public interface IGenerator
{
    Task GenerateAsync(Parser parser, string output, CancellationToken cancellationToken);
    void SetOption(string key, string? value);
    void RegisterRules(Validator validator);
    IEnumerable<(string option, object? value)> GetOptions();
}