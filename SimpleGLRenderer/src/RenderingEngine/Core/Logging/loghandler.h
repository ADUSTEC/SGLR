#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

// A pretty simple logging class
namespace SGLR {

	class Log
	{
		public:
			static void Init();
			static void Shutdown();
			inline static std::shared_ptr<spdlog::logger>& GetLogger() { return m_sptrLogger; }
		private:
			static std::shared_ptr<spdlog::logger> m_sptrLogger;
	};

}
