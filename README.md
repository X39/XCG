# How it looks

```
token integer
    require plus { 0-9 }

token scalar
    require once { integer }
    require once .
    require once { integer }

token roundO: "("
    require once (
    
token roundC: ")"
    require once )
    
token slash: "/"
    require once /
    
token star: "*"
    require once *
    
token plus: "+"
    require once +
    
token minus: "-"
    require once -

production expC
    alternatives
        match "(" @[value]expA ")"
        match @[value]scalar
        match @[value]integer

left-recursive expB
	match @[left]expB "/" @[right]expC
		set capture op '/'
	match @[left]expB "*" @[right]expC
		set capture op '*'
	match @[left]expC

left-recursive expA
	match @[left]expA "+" @[right]expB
		set capture op '+'
	match @[left]expA "-" @[right]expB
		set capture op '-'
	match @[left]expB

production main
    match @[root]expA
```

# Using XCG
`xcg -i .\input.xcg -g cpp -o output --options -s namespace:xcg::parser`
```
  -i PATH ..., --input=PATH ...                  Required. Declares a single input xcg file.

  -g GENERATOR, --generator=GENERATOR            Required. Sets the generator to use. Might be a path to a file or one of the build-in ones.

  -o PATH, --output=PATH                         (Default: output) Set the output filepath to where the generated file(s) should be generated to.

  -s OPTION:VALUE ..., --set=OPTION:VALUE ...    Allows to change generator-dependant settings.

  --options                                      Lists all options of a given generator.

  -d, --dry-run                                  Will not generate any output files if set.

  --help                                         Display this help screen.

  --version                                      Display version information.
```

# Available generators

- `cpp`

# FAQ

## Why .Net Core
Answering this question is quite simple:

I chose .net core because the whole project started out as a draft of ideas
and it was clear that i needed a solid string type which is easy to work with,
some no-f-given memory management (aka garbage collection) because generating a parser is hard enough
so making a tree structure should not take as much time as building the parser
plus it allows fast prototyping with checked typing.

The project itself was needed because writing the parser i desired myself
failed multiple times due to basic mistakes i did that would
require changing the whole syntax file because i only noticed in the end
(yes, i know about bison ... but bison + ambiguous grammar = nono).
This project allowed me to toy around with those ideas, make
things work fast and so on.

The ***TL;DR*** thus is probably ... because i can