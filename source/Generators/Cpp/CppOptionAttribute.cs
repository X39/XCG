﻿using System;

namespace XCG.Generators.Cpp
{
    [AttributeUsage(AttributeTargets.Property)]
    internal class CppOptionAttribute : Attribute
    {
        public CppOptionAttribute(string v)
        {
            Name = v;
        }

        public string Name { get; }
        public bool Nullable { get; set; }
    }
}