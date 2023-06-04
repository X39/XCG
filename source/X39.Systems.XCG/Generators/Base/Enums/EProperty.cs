namespace X39.Systems.XCG.Generators.Base.Enums;

public enum EProperty
{
    /// <summary>
    /// Invalid value.
    /// </summary>
    Invalid,

    /// <summary>
    /// The length of a <see cref="EType.CharacterCollection"/> type.
    /// </summary>
    CharacterCollectionLength,

    /// <summary>
    /// Checks whether a value of type <see cref="EType.OptionalSize"/> is set or not.
    /// </summary>
    HasValue,

    /// <summary>
    /// Receives a value of type <see cref="EType.OptionalSize"/>.
    /// </summary>
    GetValue
}