#pragma once

#include "Logger.h"
#include "Defines.h"

#include <string>
#include <memory>



namespace pul {
	class EngineLogger
	{
	public:
		PUL_API static void Init(Logger::LogLevel level);
		PUL_API static Logger& getLogger();

	private:
		inline static std::atomic<bool> m_Initialised { false };
		inline static Logger s_Logger{ Logger{} };
	};
}


#ifdef _MSC_VER
	#ifdef _DEBUG
		#define PUL_INFO(x) EngineLogger::getLogger().Info(x)
	#else
		#define PUL_INFO(x)
	#endif
#else
	#define PUL_INFO(x)
#endif