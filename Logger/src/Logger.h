#pragma once

#include <string>
#include <thread>


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
	};
}
