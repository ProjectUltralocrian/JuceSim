#pragma once

#include <string>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <iostream>


namespace pul {
	class Logger
	{
	public:
		enum class LogLevel
		{
			Debug = 1,
			Info = 3,
			Warning = 5,
			Error = 7,
			Fatal = 9
		};
		Logger(LogLevel level = LogLevel::Info);
		~Logger();
		void Info(std::string_view msg) const;
		static const char* toString(LogLevel level);
	private:
		std::ostream& m_OutStream { std::cout };
		std::atomic<bool> m_Finished{ false };
		std::jthread m_Thread; 
		mutable std::queue<std::string> m_LogQueue;
		mutable std::mutex m_Mutex;
		mutable std::condition_variable m_CondVar;
		void Worker();
		void log(std::string_view msg, LogLevel level);
	};
	std::ostream& operator<<(std::ostream& stream, Logger::LogLevel level);
}
