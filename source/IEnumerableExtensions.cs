using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace XCG
{
    public static class IEnumerableExtensions
    {
        public static IEnumerable<T> NotNull<T>(this IEnumerable<T?> ts) where T : class
        {
            return ts.Where((t) => t is not null)!;
        }
    }
}
