#include "EngineLogger.h"

namespace pul {
	void EngineLogger::Info(std::string_view msg) const
	{
		m_Logger.Info(msg);
	}
}
