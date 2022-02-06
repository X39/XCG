using System;
using System.Runtime.Serialization;

namespace XCG.Validation;

[Serializable]
internal class KeyAlreadyPresentException : Exception
{
    public string Realm { get; }
    public int Code { get; }

    public KeyAlreadyPresentException(string realm, int code)
        : base($"Cannot add rule as another one with the same realm and code already exists.")
    {
        Realm = realm;
        Code = code;
    }

    protected KeyAlreadyPresentException(SerializationInfo info, StreamingContext context) : base(info, context)
    {
        Realm = (string) info.GetValue(nameof(Realm), typeof(string))!;
        Code = (int) info.GetValue(nameof(Code), typeof(int))!;
    }

    public override void GetObjectData(SerializationInfo info, StreamingContext context)
    {
        base.GetObjectData(info, context);
        info.AddValue(nameof(Realm), Realm);
        info.AddValue(nameof(Code), Code);
    }
}