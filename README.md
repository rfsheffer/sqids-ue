# Unreal Engine Plugin Implementation of sqids-cpp
"Sqids (pronounced "squids") is an open-source library that lets you generate short unique identifiers from numbers. These IDs are URL-safe, can encode several numbers, and do not contain common profanity words."

See https://sqids.org/cpp

Built with Unreal 5.3, but should support versions as old as 4.27

Only two functions for the library itself:

* SqidsEncode
* SqidsDecode

These are basically the same as Sqids own versions but take in extra settings for controlling MinLength and CustomAlphabet

And a helper for generating random alphabets if needed
* SqidsGenerateRandomAlphabet

# License
Same as Sqids, MIT
