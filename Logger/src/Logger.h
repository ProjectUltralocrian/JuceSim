#pragma once

#include <string>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

namespace pul {
	class Logger
	{
	public:
		Logger();
		~Logger();
		void Info(std::string_view msg) const;
	private:
		void Worker() const;
		std::atomic<bool> m_Finished{ false };
		std::jthread m_Thread; 
		mutable std::queue<std::string> m_LogQueue;
		mutable std::mutex m_Mutex;
		mutable std::condition_variable m_CondVar;
	};
}
