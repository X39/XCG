﻿using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;
using X39.Systems.XCG.Parsing;
using X39.Systems.XCG.Validation;

namespace X39.Systems.XCG;

public interface IGenerator
{
    Task GenerateAsync(Parser parser, string output, CancellationToken cancellationToken);
    void SetOption(string key, string? value);
    void RegisterRules(Validator validator);
    IEnumerable<(string option, object? value)> GetOptions();
}