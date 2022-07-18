using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using XCG.Generators.CSharp;
using XCG.Parsing;
using XCG.Validation;

namespace XCG.Generators.Base;

public abstract class BaseGenerator<TOptions> : IGenerator
    where TOptions : class
{
    protected abstract TOptions Options { get; }

    public Task GenerateAsync(Parser parser, string output, CancellationToken cancellationToken)
    {
        var cstVisitor = new CstVisitor(parser);
        var ast = cstVisitor.Accumulate();
        throw new NotImplementedException();
    }

    protected abstract Task WriteFiles(IEnumerable<Group> functionGroups, string output);

    public void SetOption(string key, string? value)
    {
        var properties = typeof(TOptions)
            .GetProperties(System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.Instance);
        var dict = properties.Select((q) => new
            {
                att = q.GetCustomAttributes(true).OfType<CSharpOptionAttribute>()
                    .FirstOrDefault(),
                prop = q
            }).Where((q) => q.att is not null)
            .ToDictionary((q) => q.att!.Name.ToLower(), (q) => new {att = q.att!, q.prop});

        if (dict.TryGetValue(key.ToLower(), out var a))
        {
            if (!a.att.Nullable && value is null)
            {
                throw new NullReferenceException($@"The option ""{a.att.Name}"" cannot be null.");
            }

            a.prop.SetValue(Options, value is null ? null : Convert.ChangeType(value, a.prop.PropertyType));
        }
        else
        {
            throw new KeyNotFoundException($@"The option ""{key}"" was not found.");
        }
    }

    public virtual void RegisterRules(Validator validator)
    {
    }

    public IEnumerable<(string option, object? value)> GetOptions()
    {
        var properties = typeof(TOptions)
            .GetProperties(System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.Instance);
        return properties.Select((q) => new
            {
                prop = q,
                att = q.GetCustomAttributes(true).OfType<CSharpOptionAttribute>()
                    .FirstOrDefault()
            }).Where((q) => q.att is not null)
            .Select((q) => (option: q.att!.Name.ToLower(), value: q.prop.GetValue(Options)));
    }
}