namespace XCG.Generators.Base.Enums;

public enum EType
{
    /// <summary>
    /// A type that is associated with a void (non existing) value.
    /// </summary>
    Void,

    /// <summary>
    /// The type that is being used when working with files.
    /// </summary>
    FileOffset,

    /// <summary>
    /// Simple integer type. Size should be the one that is usually
    /// used for this in the targeted language.
    /// </summary>
    Integer,

    /// <summary>
    /// A collection of characters.
    /// Characteristics must include:
    /// <list type="bullet">
    ///     <item>Length</item>
    ///     <item>Index-Access</item>
    /// </list>
    /// </summary>
    CharacterCollection,

    /// <summary>
    /// The type that is usually associated with sizes of eg. collections.
    /// </summary>
    Size,

    /// <summary>
    /// The same as <see cref="Size"/> but can be assigned a nil value.
    /// </summary>
    OptionalSize,

    /// <summary>
    /// A single character of a string.
    /// </summary>
    Character,

    /// <summary>
    /// A value of the type boolean that can be either true or false.
    /// </summary>
    Boolean,
}