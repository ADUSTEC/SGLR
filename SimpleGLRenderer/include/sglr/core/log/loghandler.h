#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

// A pretty simple logging class
namespace sglr {

	class log
	{
		public:
			static void init();
			static void shutdown();
			inline static std::shared_ptr<spdlog::logger>& getLogger() { return m_sptrLogger; }
		private:
			static std::shared_ptr<spdlog::logger> m_sptrLogger;
	};

}
