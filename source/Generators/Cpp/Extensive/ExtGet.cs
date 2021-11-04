using System;

namespace XCG.Generators.Cpp.Extensive
{
    internal static class ExtGet
    {
        public static string GetEvaluatedValue(this Parsing.Statements.Get get, CppOptions cppOptions, string stateTypeName)
        {
            switch (get.ActiveScope)
            {
                case Parsing.EActiveScope.capture:
                    switch (get.Mode)
                    {
                        case Parsing.EMode.GetProperty:
                            return $"{Constants.ClassInstanceVariable}->{get.Property.ToCppName()}.value()";
                        case Parsing.EMode.GetMapProperty:
                        case Parsing.EMode.GetListIndex:
                            throw new NotImplementedException();
                        case Parsing.EMode.GetListPop:
                            return $"[](){{ auto tmp = {Constants.ClassInstanceVariable}->{get.Property.ToCppName()}.back(); {Constants.ClassInstanceVariable}->{get.Property.ToCppName()}.pop_back(); return tmp.value(); }}()";
                        default:
                            throw new FatalException();
                    }
                case Parsing.EActiveScope.global:
                    switch (get.Mode)
                    {
                        case Parsing.EMode.GetProperty:
                            return $"this->{get.Property.ToCppName()}.value()";
                        case Parsing.EMode.GetMapProperty:
                        case Parsing.EMode.GetListIndex:
                            throw new NotImplementedException();
                        case Parsing.EMode.GetListPop:
                            return $"[](){{ auto tmp = this->{get.Property.ToCppName()}.back(); this->{get.Property.ToCppName()}.pop_back(); return tmp.value(); }}()";
                        default:
                            throw new FatalException();
                    }
                case Parsing.EActiveScope.auto:
                case Parsing.EActiveScope.local:
                    switch (get.Mode)
                    {
                        case Parsing.EMode.GetProperty:
                            return $"{Constants.StateInstanceVariable}.{get.Property.ToCppName()}.value()";
                        case Parsing.EMode.GetMapProperty:
                        case Parsing.EMode.GetListIndex:
                            throw new NotImplementedException();
                        case Parsing.EMode.GetListPop:
                            return $"[](){{ auto tmp = {Constants.StateInstanceVariable}.{get.Property.ToCppName()}.back(); {Constants.StateInstanceVariable}.{get.Property.ToCppName()}.pop_back(); return tmp.value(); }}()";
                        default:
                            throw new FatalException();
                    }
                default:
                    throw new NotImplementedException();
            }
        }
    }
}
