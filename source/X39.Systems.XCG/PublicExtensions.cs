using System;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace X39.Systems.XCG;

public static class PublicExtensions
{
    
    public static Task WriteAsync(this TextWriter writer, string value, CancellationToken cancellationToken)
    {
        return writer.WriteAsync(value.AsMemory(), cancellationToken);
    }
    public static Task WriteLineAsync(this TextWriter writer, string value, CancellationToken cancellationToken)
    {
        return writer.WriteLineAsync(value.AsMemory(), cancellationToken);
    }
    public static async Task WriteLineAsync(this TextWriter writer, int indent, string value, CancellationToken cancellationToken)
    {
        if (indent > 0)
            await writer.WriteAsync(new string(' ', 4 * indent).AsMemory(), cancellationToken);
        await writer.WriteLineAsync(value.AsMemory(), cancellationToken);
    }
    /// <summary>
    /// Returns all occurrences of <typeparamref name="T"/> inside of the <see cref="Parsing.IStatement"/>.
    /// Will not descend into the found ones.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="statement"></param>
    /// <returns></returns>
    public static IEnumerable<T> FindChildren<T>(this Parsing.IStatement statement)
    {
        foreach (var it in statement.Statements)
        {
            foreach (var found in it.FindChildren<T>())
            {
                yield return found;
            }
            if (it is T t)
            {
                yield return t;
            }
        }
    }

    /// <summary>
    /// Returns all occurrences of <typeparamref name="T"/> inside of the <see cref="Parsing.IStatement"/>.
    /// Will not descend into the found ones.
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="statement"></param>
    /// <returns></returns>
    public static IEnumerable<(T, Parsing.IStatement[])> FindChildrenWithParents<T>(this Parsing.IStatement statement)
    {
        IEnumerable<(T, Parsing.IStatement[])> Recurse(Parsing.IStatement l)
        {
            foreach (var it in l.Statements)
            {
                foreach (var (t, statements) in Recurse(it))
                {
                    yield return (t, statements.Append(l).ToArray());
                }
                if (it is T t2)
                {
                    yield return (t2, new[] { l });
                }
            }
        }
        return Recurse(statement);
    }


    /// <summary>
    /// Extracts the whole stacktrace, including possible data members and inner exceptions, from the provided exception.
    /// </summary>
    /// <param name="ex"></param>
    /// <returns></returns>
    public static string FullStackTrace(this Exception ex)
    {
        var builder = new StringBuilder();

        var indentation = 0;
        while (true)
        {
            var tab = new string(' ', indentation * 4);
            builder.Append(tab);
            builder.AppendLine(ex.GetType().FullName ?? "unavailable");

            builder.Append(tab);
            builder.AppendLine(ex.Message);

            foreach (DictionaryEntry dictionaryEntry in ex.Data)
            {
                builder.Append(tab);
                builder.Append(Convert.ToString(dictionaryEntry.Key));
                builder.Append(": ");
                builder.AppendLine(Convert.ToString(dictionaryEntry.Value));
            }

            var stackTrace = ex.StackTrace ?? "unavailable";
            builder.AppendLine(stackTrace.Replace("\n", string.Concat("\n", tab)));
            if (ex.InnerException is not null)
            {
                ex = ex.InnerException;
                indentation++;
                continue;
            }

            break;
        }
        return builder.ToString();
    }
}