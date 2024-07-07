#ifndef PUL_ENGINE_H
#define PUL_ENGINE_H

//#include "AudioProcessor.h"
#include <cmath>
#include <vector>
#include <numbers>
#include <stdexcept>



#ifdef PUL_DLL_BUILD
	#define PUL_API __declspec(dllexport) 
#else
	#define PUL_API __declspec(dllimport)
#endif


#ifdef _MSC_VER
	#ifdef _DEBUG
		#define ASSERT(x) if(!(x)) {__debugbreak();}
	#else 
		#define ASSERT
	#endif
#else
	#error "Currently only supporting Windows MSVC builds..."
#endif


namespace pul {

	class AudioProcessor;

	class NotImplementedException : public std::logic_error
	{
	public:
		NotImplementedException() : std::logic_error("Function not yet implemented") { }
	};


	/**
	* @brief Generates a std::array of specified size, and fills it with values
	*		 so that the values in the array provide a lookup-table for a single
	*		 full sine-wave cycle (2 * PI radians).
	* @param SampleType type of the sample, usually double or float.
	* @param NumSamplesInFullSinCycle number of values in the array / full sine wave cycle (must be non-negative)
	*/
	template<typename SampleType, size_t NumSamplesInFullSinCycle>
		requires std::is_trivial_v<SampleType>
	constexpr std::array<SampleType, NumSamplesInFullSinCycle> 
		getSinSampleValues() noexcept
	{
		std::array<SampleType, NumSamplesInFullSinCycle> output;
		for (size_t i = 0; i < NumSamplesInFullSinCycle; ++i)
		{
			output[i] = std::sin(i * std::numbers::pi_v<SampleType> *2 / NumSamplesInFullSinCycle);
		}
		return output;
	}

	class PUL_API AudioEngine
	{
	public:
		virtual void run();
		virtual void registerAudioProcessor(AudioProcessor* processor);
		virtual std::vector<AudioProcessor*> getAudioProcessors() const;
		virtual ~AudioEngine() = default;
	private:
		std::vector<AudioProcessor*> m_Processors{};
	};
}

#endif //PUL_ENGINE_H