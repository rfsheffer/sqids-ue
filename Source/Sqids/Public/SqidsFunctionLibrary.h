
#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "SqidsFunctionLibrary.generated.h"

/**
 * Advanced Settings to pass into SqidsEncode and SqidsDecode
 * You can generate proper alphabets using SqidsGenerateRandomAlphabet
 */
USTRUCT(BlueprintType)
struct FSqidsSettings
{
	GENERATED_BODY()

	// The minimum length of ID to generate. 0 means use default.
	UPROPERTY(BlueprintReadWrite, Category="Sqids")
	uint8 MinLength = 0;

	// A custom alphabet to control the randomness factor. Empty means use default.
	// NOTE: Alphabets must have all unique characters or numbers.
	UPROPERTY(BlueprintReadWrite, Category="Sqids")
	FString CustomAlphabet;
};

/**
 * Sqids (pronounced "squids") is an open-source library that lets you generate short unique
 * identifiers from numbers. These IDs are URL-safe, can encode several numbers, and do not
 * contain common profanity words.
 * Sqids is Good For:
 * - Encoding primary keys : If you're using a relational database
 * - Saving database lookups : By encoding multiple objects
 * - Temporary login tokens : Profanity-free and URL-safe
 * Sqids is Bad For:
 * - Sensitive data : This is not an encryption library
 * - User IDs: Can reveal user count if anyone finds out the encoding alphabet
 */
UCLASS()
class SQIDS_API USqidsFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	///
	/// Encode a sequence of integers into an ID.
	///
	/// These are the cases where encoding might fail:
	///   - One of the numbers passed is smaller than 0 or greater than `maxValue`
	///   - An /n/ number of attempts has been made to re-generated the ID, where
	///     /n/ is the length of the alphabet + 1
	///
	/// Prints to log When encoding fails
	///
	/// @param numbers The integers to encode into an ID
	/// @param idOut The ID out on success
	/// @param settings Extra settings to control Sqids. Should be used in decoding later.
	/// @return        True on success
	///
	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay="2", AutoCreateRefTerm="settings"), Category="Sqids")
	static bool SqidsEncode(const TArray<int32>& numbers, FString& idOut, const FSqidsSettings& settings);

	///
	/// Decode an ID back into a sequence of integers. This function will return
	/// an empty sequence in the following cases:
	///   - The ID is empty
	///   - An invalid ID is passed
	///   - A non-alphabet character is found in the ID
	///
	/// @param idIn  The ID to decode
	/// @param numbersOut The decoded numbers
	/// @param settings Extra settings to control Sqids. Should be used in decoding later.
	///
	UFUNCTION(BlueprintCallable, meta=(AdvancedDisplay="2", AutoCreateRefTerm="settings"), Category="Sqids")
	static void SqidsDecode(const FString& idIn, TArray<int32>& numbersOut, const FSqidsSettings& settings);

	/**
	 * Generate a random alphabet for Squids to use.
	 * @param randStream Random stream to pull from
	 * @param alphabetOut The alphabet generated with the stream
	 */
	UFUNCTION(BlueprintCallable, Category="Sqids")
	static void SqidsGenerateRandomAlphabet(const FRandomStream& randStream, FString& alphabetOut);
};
