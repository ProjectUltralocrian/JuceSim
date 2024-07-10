#include "EngineLogger.h"

namespace pul {
	void EngineLogger::Init(Logger::LogLevel level)
	{
		//s_Logger = std::make_shared<Logger>(level);
		s_Logger.Info("Logger initialised...");
	}
	Logger& EngineLogger::getLogger()
	{
		return s_Logger;
	}
}
