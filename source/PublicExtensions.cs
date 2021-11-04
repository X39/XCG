using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace XCG
{
    public static class PublicExtensions
    {
        /// <summary>
        /// Returns all <typeparamref name="T"/> in <paramref name="ts"/>
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="ts"></param>
        /// <returns></returns>
        public static IEnumerable<T> WhereIs<T>(this IEnumerable ts) where T : class
        {
            foreach (var it in ts)
            {
                if (it is T t)
                {
                    yield return t;
                }
            }
        }

        /// <summary>
        /// Ensures that only non-null elements are returned.
        /// Equivalent to calling
        /// <code>ts.Where((t) => t is not null)</code>
        /// and dropping the nullability afterwards.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="ts"></param>
        /// <returns></returns>
        public static IEnumerable<T> NotNull<T>(this IEnumerable<T?> ts) where T : class
        {
            return ts.Where((t) => t is not null)!;
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
}

