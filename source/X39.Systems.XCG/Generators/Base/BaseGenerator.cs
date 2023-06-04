using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;
using X39.Systems.XCG.Generators.Base.Parts;
using X39.Systems.XCG.Parsing;
using X39.Systems.XCG.Validation;
using X39.Util;

namespace X39.Systems.XCG.Generators.Base;

public abstract class BaseGenerator<TOptions> : IGenerator
    where TOptions : class
{
    protected TOptions Options { get; }

    protected BaseGenerator()
        : this(typeof(TOptions).CreateInstance<TOptions>())
    {
    }

    protected BaseGenerator(TOptions options)
    {
        Options = options;
    }

    public Task GenerateAsync(Parser parser, string output, CancellationToken cancellationToken)
    {
        var cstVisitor = new CstVisitor(parser);
        cstVisitor.Accumulate();
        return WriteFiles(cstVisitor.Groups, output, cancellationToken);
    }

    protected abstract Task WriteFiles(
        IEnumerable<Group> functionGroups,
        string output,
        CancellationToken cancellationToken);

    public void SetOption(string key, string? value)
    {
        var properties = typeof(TOptions)
            .GetProperties(System.Reflection.BindingFlags.Public | System.Reflection.BindingFlags.Instance);
        var dict = properties.Select(
                (q) => new
                {
                    att = q.GetCustomAttributes(true)
                        .OfType<GeneratorOptionAttribute>()
                        .FirstOrDefault(),
                    prop = q,
                })
            .Where((q) => q.att is not null)
            .ToDictionary((q) => q.att!.Name.ToLower(), (q) => new {att = q.att!, q.prop});

        if (dict.TryGetValue(key.ToLower(), out var a))
        {
            if (!a.prop.IsNullable() && value is null)
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
        return properties.Select(
                (q) => new
                {
                    prop = q,
                    att = q.GetCustomAttributes(true)
                        .OfType<GeneratorOptionAttribute>()
                        .FirstOrDefault(),
                })
            .Where((q) => q.att is not null)
            .Select((q) => (option: q.att!.Name.ToLower(), value: q.prop.GetValue(Options)));
    }
}