#include "Logger.h"

#include <iostream>
#include <format>
#include <future>
#include <chrono>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>


static std::queue<std::string> logQueue;
static std::mutex mtx;
static std::condition_variable cv;


using namespace std::literals;

namespace pul {
	Logger::Logger()
		: m_Thread{ [this]() {Worker(); } }
	{

		/*std::this_thread::sleep_for(4000ms);
		std::cout << std::format("[INFO] Finished logging...");
		Info("Finished logging...");
		m_Finished = true;
		m_Thread.join();
		*/
	}
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
			std::lock_guard<std::mutex> lock(mtx);
			logQueue.push(msg.data());
		}
		cv.notify_one();
		
	}
	void Logger::Worker() const
	{
		Info("Initializing Logger on separate thread...");
		while (!m_Finished)
		{
			std::unique_lock<std::mutex> lock(mtx);
			cv.wait(lock, [] { return !logQueue.empty(); }); // Wait until there's a log message
			std::string msg = logQueue.front();
			logQueue.pop();
			lock.unlock();

			// Process the log message (e.g., write to a file, send over network, etc.)
			std::cout << std::format("[INFO] {}\n", msg);
		}
	}
}