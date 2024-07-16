#ifndef PUL_ENGINE_H
#define PUL_ENGINE_H

#include "Defines.h"
#include "lua_wrapper.h"
#include "Observer.h"
#include "EngineLogger.h"



#include <cmath>
#include <vector>
#include <numbers>
#include <stdexcept>
#include <array>
#include <optional>

namespace pul {
	class AudioProcessor;
	class PluginLoader;

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

	class AudioEngine : public Broadcaster
	{
	public:
		PUL_API AudioEngine() = default;
		PUL_API virtual ~AudioEngine();
		PUL_API virtual void run();
		PUL_API virtual void registerAudioProcessor(AudioProcessor* processor);
		PUL_API virtual void deregisterAudioProcessor(AudioProcessor* processor);
		PUL_API virtual std::vector<AudioProcessor*> getAudioProcessors() const;
		
		
		PUL_API void registerListener(Listener* listener) override;
		PUL_API void deregisterListener(Listener* listener) override;


		/**
		 * @brief Implementing the notify function of the Broadcaster interface.
		 *        Sends a notification to all registered listeners.
		 * @param msg: The message to be sent along with a reference to the broadcaster.
		 */
		PUL_API void notify(std::string_view msg) const override;

		/**
		 * @brief Simulating the play functionality of a daw (e.g. loading audio buffers and sending
		 *        them to registered processors for processing.
		 */
		PUL_API virtual void play();
		inline float getVolume() const { return m_Volume; }
		PUL_API void setVolume(float newVolume);

		/**
		 * @brief Gets plugins from specified Lua config file. The names of the dll's
		 *		  should be listed as strings in Lua table, in a variable called "plugins".
		 *		  If the specified config file doesn't exist, if the "plugins" table doesn't
		 *		  exist, or there are no correct dll's in the table, this function logs a
		          relevant error message, but otherwise does nothing.
		 * @param luaFileName: The name of the Lua config file.
		 */
		PUL_API void getAndRegisterPluginsFromLua(const char* luaFileName);

	protected:
		LuaInstance m_Lua{};
		std::vector<PluginLoader*> m_Loaders{};

	private:
	    
		/**
		 * @brief m_Listeners MUST precede declaration of m_Processors,
		 *        otherwise the destruction will take place in the incorrect order...
		 */
		std::vector<Listener*> m_Listeners;

		std::vector<AudioProcessor*> m_Processors{};

		/**
		 * @brief
		 */
		float m_Volume{ 0.f };

		EngineLogger m_Logger{};

		std::optional<std::vector<std::string>> getDllNamesFromLua(const char* luaFileName, const char* varName);
	};
}

#endif //PUL_ENGINE_H