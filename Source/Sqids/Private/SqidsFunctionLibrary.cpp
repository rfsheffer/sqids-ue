
#include "SqidsFunctionLibrary.h"
#include "SqidsModule.h"
#include "sqids/sqids.hpp"

namespace
{
	const char* sDefaultAlpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

	template <typename RangeType>
	void RandomSeededShuffle(const FRandomStream& randStream, RangeType& Range)
	{
		auto Data = GetData(Range);

		using SizeType = decltype(GetNum(Range));
		const SizeType Num = GetNum(Range);

		for (SizeType Index = 0; Index < Num - 1; ++Index)
		{
			// Get a random integer in [Index, Num)
			const SizeType RandomIndex = Index + static_cast<SizeType>(randStream.RandHelper(Num - Index));
			if (RandomIndex != Index)
			{
				Swap(Data[Index], Data[RandomIndex]);
			}
		}
	}
}

bool USqidsFunctionLibrary::SqidsEncode(const TArray<int32>& numbers, FString& idOut, const FSqidsSettings& settings)
{
	if(numbers.Num() == 0)
	{
		return false;
	}
	
	bool success = false;
	try
	{
		// Create options
		sqidscxx::SqidsOptions sSqidsOptions;
		sSqidsOptions.minLength = settings.MinLength;
		if(settings.CustomAlphabet.Len() != 0)
		{
			sSqidsOptions.alphabet = StringCast<ANSICHAR>(*settings.CustomAlphabet).Get();
		}
		else
		{
			sSqidsOptions.alphabet = sDefaultAlpha;
		}

		// Do Encode
		sqidscxx::Sqids sqids(sSqidsOptions);
		auto id = sqids.encode(std::vector<uint64>(numbers.GetData(), numbers.GetData() + numbers.Num()));

		// Convert and return results
		idOut = StringCast<TCHAR>(id.c_str());
		success = true;
	}
	catch(std::exception er)
	{
		UE_LOG(LogSqids, Error, TEXT("%hs"), er.what());
	}
	
	return success;
}

void USqidsFunctionLibrary::SqidsDecode(const FString& idIn, TArray<int32>& numbersOut, const FSqidsSettings& settings)
{
	numbersOut.Reset();
	try
	{
		// Create options
		sqidscxx::SqidsOptions sSqidsOptions;
		sSqidsOptions.minLength = settings.MinLength;
		if(settings.CustomAlphabet.Len() != 0)
		{
			sSqidsOptions.alphabet = StringCast<ANSICHAR>(*settings.CustomAlphabet).Get();
		}
		else
		{
			sSqidsOptions.alphabet = sDefaultAlpha;
		}
		
		// Do Decode
		sqidscxx::Sqids sqids(sSqidsOptions);
		auto numbers = sqids.decode(StringCast<ANSICHAR>(*idIn).Get());

		// Convert and return results
		numbersOut.Reset(numbers.size());
		for(const auto &num : numbers)
		{
			numbersOut.Add(num);
		}
	}
	catch(std::exception er)
	{
		UE_LOG(LogSqids, Error, TEXT("%hs"), er.what());
	}
}

void USqidsFunctionLibrary::SqidsGenerateRandomAlphabet(const FRandomStream& randStream, FString& alphabetOut)
{
	alphabetOut = StringCast<TCHAR>(sDefaultAlpha).Get();
	RandomSeededShuffle(randStream, alphabetOut);
}
