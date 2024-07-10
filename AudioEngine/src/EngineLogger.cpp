#include "EngineLogger.h"

namespace pul {
	void EngineLogger::Init(Logger::LogLevel level)
	{
		s_Logger.Info("Logger initialised...");
		m_Initialised = true;
	}
	Logger& EngineLogger::getLogger()
	{
		ASSERT(m_Initialised);
		return s_Logger;
	}
}
