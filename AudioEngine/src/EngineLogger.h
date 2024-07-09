#pragma once

#include "Logger.h"
#include <string>

#ifdef _MSC_VER
	#ifdef _DEBUG
		#define PUL_INFO(x) m_Logger.Info(x)
	#else
		#define PUL_INFO(x)
	#endif
#else
	#define PUL_INFO(x)
#endif

namespace pul {
	class EngineLogger
	{
	public:
		void Info(std::string_view msg) const;

	private:
		Logger m_Logger{};


	};
}