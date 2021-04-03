﻿using XCG.Parsing;
using XCG.Validation;

namespace XCG
{
    public interface IGenerator
    {
        void Generate(Parser parser, string output);
        void SetOption(string key, string? value);
        void RegisterRules(Validator validator);
    }
}