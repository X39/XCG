using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
        /// Returns all occurances of <typeparamref name="T"/> inside of the <see cref="Parsing.IStatement"/>.
        /// Will not descend into the found ones.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="statement"></param>
        /// <returns></returns>
        public static IEnumerable<T> FindChildren<T>(this Parsing.IStatement statement)
        {
            foreach (var it in statement.Statements)
            {
                if (it is T t)
                {
                    yield return t;
                }
                else
                {
                    foreach (var found in it.FindChildren<T>())
                    {
                        yield return found;
                    }
                }
            }
        }

        /// <summary>
        /// Returns all occurances of <typeparamref name="T"/> inside of the <see cref="Parsing.IStatement"/>.
        /// Will not descend into the found ones.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="statement"></param>
        /// <returns></returns>
        public static IEnumerable<(T, Parsing.IStatement[])> FindChildrenWithParents<T>(this Parsing.IStatement statement)
        {
            IEnumerable<(T, Parsing.IStatement[])> recurse(Parsing.IStatement l)
            {
                foreach (var it in l.Statements)
                {
                    if (it is T t)
                    {
                        yield return (t, new Parsing.IStatement[] { l });
                    }
                    else
                    {
                        foreach (var found in recurse(it))
                        {
                            yield return (found.Item1, found.Item2.Append(l).ToArray());
                        }
                    }
                }
            }
            return recurse(statement);
        }


        /// <summary>
        /// Extracts the whole stacktrace, including possible datamembers and inner exceptions, from the provided exception.
        /// </summary>
        /// <param name="exception"></param>
        /// <returns></returns>
        public static string FullStackTrace(this Exception exception)
        {
            StringBuilder builder = new StringBuilder();
            void recurse(Exception ex, int intendation)
            {
                var tab = new string(' ', intendation * 4);
                builder.Append(tab);
                builder.AppendLine(ex.GetType().FullName ?? "unavailable");

                builder.Append(tab);
                builder.AppendLine(ex.Message ?? "unavailable");

                foreach (System.Collections.DictionaryEntry dictionaryEntry in ex.Data)
                {
                    builder.Append(tab);
                    builder.Append(Convert.ToString(dictionaryEntry.Key));
                    builder.Append(": ");
                    builder.AppendLine(Convert.ToString(dictionaryEntry.Value));
                }

                var stackTrace = ex.StackTrace ?? "unavailable";
                builder.AppendLine(stackTrace.Replace("\n", String.Concat("\n", tab)));
                if (ex.InnerException is not null)
                {
                    recurse(ex.InnerException, intendation + 1);
                }
            }
            recurse(exception, 0);
            return builder.ToString();
        }
    }
}

