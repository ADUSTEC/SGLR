#include "loghandler.h"
#include "log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace SGLR {

	std::shared_ptr<spdlog::logger> Log::m_sptrLogger; // define static variable to store logger

	void Log::Init()
	{
		spdlog::set_pattern("%^(%n) [%Y-%m-%d %H:%M:%S]: %v%$"); // (NAME) [YEAR MONTH DAY - HOURS MINUTES SECONDS]: Logged message
		// time is written in the 24-hour format

		m_sptrLogger = spdlog::stderr_color_mt("->SGLR"); // sets name of the logger to SGLR
		m_sptrLogger->set_level(spdlog::level::trace);

	}

	void Log::Shutdown() {
		spdlog::shutdown();
	}

}
