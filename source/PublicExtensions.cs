using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG
{
    public static class PublicExtensions
    {
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
    }
}
