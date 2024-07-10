#include "Logger.h"
#include <iostream>
#include <format>

using namespace std::literals;

namespace pul {
	Logger::Logger(Logger::LogLevel level)
		: m_Thread{
		[this]() {Worker(); }
	} {}


	Logger::~Logger()
	{
		Info("Shutting down logger...");
		if (m_Thread.joinable()) {
			Info("Joinable");
			m_Finished = true;
			m_Thread.join();
		}
	}

	void Logger::Info(std::string_view msg) const
	{
		{
			std::lock_guard<std::mutex> lock(m_Mutex);
			m_LogQueue.push(msg.data());
		}
		m_CondVar.notify_one();
	}

	void Logger::Worker()
	{
		while (!m_Finished)
		{
			std::unique_lock<std::mutex> lock(m_Mutex);
			m_CondVar.wait(lock, [&] { return !m_LogQueue.empty(); }); // Wait until there's a log message
			std::string msg = m_LogQueue.front();
			m_LogQueue.pop();
			lock.unlock();

			// Process the log message (e.g., write to a file, send over network, etc.)
			log(msg, LogLevel::Warning);
		}
	}
	void Logger::log(std::string_view msg, LogLevel level)
	{
		m_OutStream << std::format("[{}] {}\n", toString(level), msg);

	}
	const char* Logger::toString(LogLevel level)
	{
		auto output = [lv = level]()
			{
				switch (lv) {
				case Logger::LogLevel::Debug: return "DEBUG";
				case Logger::LogLevel::Info: return "INFO";
				case Logger::LogLevel::Warning: return "WARNING";
				case Logger::LogLevel::Error: return "ERROR";
				case Logger::LogLevel::Fatal: return "FATAL";
				default: return "";
				};
			}();
		return output;
	}
	std::ostream& operator<<(std::ostream& stream, Logger::LogLevel level)
	{
		
		return stream << Logger::toString(level);
	}
}