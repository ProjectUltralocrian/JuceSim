#ifndef HELPERS_H
#define HELPERS_H

#include <cmath>
#include <array>
#include <numbers>



#ifdef _DEBUG
	#ifdef _MSC_VER
		#define ASSERT(x) if(!(x)) {__debugbreak();}
	#endif
#else
	#define ASSERT
#endif


namespace pul {


	class NotImplementedException : public std::logic_error
	{
	public:
		NotImplementedException() : std::logic_error("Function not yet implemented") { };
	};

	
	/**
	* @brief Generates a std::array of specified size, and fills it with values
	*		 so that the values in the array provide a lookup-table for a single 
	*		 full sine-wave cycle (2 * PI radians).
	* @param SampleType type of the sample, usually double or float.
	* @param NumSamplesInFullSinCycle number of values in the array / full sine wave cycle (must be non-negative)
	*/
	template<typename SampleType, size_t NumSamplesInFullSinCycle>
	constexpr std::array<SampleType, NumSamplesInFullSinCycle> getSinSampleValues() noexcept
	{
		std::array<SampleType, NumSamplesInFullSinCycle> output;
		for (size_t i = 0; i < NumSamplesInFullSinCycle; ++i)
		{
			output[i] = std::sin(i * std::numbers::pi_v<SampleType> * 2 / NumSamplesInFullSinCycle);
		}
		return output;
	}
}

#endif // !HELPERS_H
