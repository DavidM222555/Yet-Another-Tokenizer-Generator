# Yet-Another-Tokenizer-Generator
This project is my attempt at, first, creating a tokenizer and from there I hope to then integrate it with a parser. Effectively, I'm trying to replicate 
the famous programming language creation program Flex and Bison.

Currently I have implemented the basics for user generated patterns for lexemes and the generation of NFAs for recognizing tokens that fit those regex patterns.

# File Specification
For the lexer to properly recognize your lexeme specifications it must 
follow this basic format: <br/>
```
[Any amount of white space or newlines]
$LEXEMES
LexemeLabel,RegexForLexeme,Precedence
...
$$LEXEMES
```

# Utilities
- Can tokenize basic alphanumeric regex strings such as (1|2...)* and (a|b|c...)*. For this see the example main program 
with TestInput1.txt.

# Issues
- Right now I am working through the handling and parsing of escaped characters in my regex processing. 
For example, if I wanted to process a regex for '*' I would run into issues because that is the operator
for the Kleene star in my regex but that is obviously an important lexeme for arithmetic expressions.
- After handling the above I plan to add support for character classes such as [a-z] or /d for digits.
