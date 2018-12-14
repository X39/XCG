# FAQ
## What is this?
X39s Code Generator (or short XCG) is a tool i created mostly for myself to make parser generation more simple.
It allows you to generate a CST without any additional steps required but providing the input file.
## Is there any example input file available?
Yes, the whole parser of this project is generated with the tool itself. The input file is located [here](https://github.com/X39/XCG/blob/master/XCG/ebnf.txt)

## How to use this?
From the `xcg -?` output:

    Usage: xcg -i <path> -o <name>
        -i    Sets the input BNF file. Should be a valid path.
              Will be passed straigth into fopen(...)!

        -o    Sets the file names for the generation output.
              Please note that theese are not allowed to
              be a path and have to be a valid filename.
              Moving output to a different directory then
              where the tool is located is not supported.

        -t    Prints the whole BNF parsing tree after generating.

        -T    Same as `-t` but minimizes the tree first.

        -v    Prints current version informations and terminates
              with exit code 0.

    BNF Documentation:
        - Annotation:
            Annotations have to be at the very start of each file.
            They allow you to change some flags in the generator
            which modify the output.
            Available annotations are:
                - @SKIP
                    Expects the characters that should be skipped.
                    defaults to " \r\n\t".
                - @LINECOMMENTSTART
                    Tells what a linecomment-start looks like.
                    defaults to "\\".
                - @CASESENSITIVE
                    Allows parsing of test-tokens to be either
                    case-sensitive or not.
                    Please note that this has no effect on
                    tokens that are non-text tokens.
                    --> `(a-z)` is no text-token
                    --> `abc` is a text-token
                    defaults to "false".
                    value has to be either
                    `true` or `false`.
        - Tokens:
            Tokens are character-combinations that can be
            used in statements.
            The tokens always have to be lowercase!
            A token consists of:
                - A name
                - An optional representation for errors
                - the actual token
                - Optional token mods
            The syntax of a token somewhat resembles regex,
            but do not be fooled! It is no actual regex
            involved!
            Usage:
                name = "representation" > token ? tokenmod
                name => token
                name => token ? tokenmod ? tokenmod
            Allowed stuff for tokens:
                - alphanumerical characters
                - backspace escaped anything
            Special syntax constructs:
                `?-?` will check for a given range.
                `(?)` allows to group a token together.
                `(?)+` allows repeat a group.
                `.` placeholder for ANY character but '\0'.
            Available tokenmods:
                notoken - Prevents token generation so that
                          it does not appears inside the
                          generated tree.
        - Statements:
            Statements are rules about how to parse something.
            They always have to be named fully uppercase.
            Usage (Expressions is the actual content):
                NAME = <EXPRESSIONS>;            Syntax constructs:
                `(?)` Allows grouping
                `[?]` Allows to conditional execute
                `{?}` Will repeatedly parse whatever is inside
            Example:
                STATEMENT = token1 OTHERSTATEMENT { token2 };
            For more info, checkout the wikipedia page to BNF :)
