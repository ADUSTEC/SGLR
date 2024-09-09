#pragma once

#include "loghandler.h"


// Debug only logging macros
#ifdef _DEBUG

#define LOG_BREAK __debugbreak(); // Windows only

#define LOG_FATAL(...)           ::SGLR::Log::GetLogger()->critical(__VA_ARGS__)
#define LOG_ERROR(...)           ::SGLR::Log::GetLogger()->error(__VA_ARGS__)
#define LOG_WARN(...)            ::SGLR::Log::GetLogger()->warn(__VA_ARGS__)
#define LOG_DEBUG(...)           ::SGLR::Log::GetLogger()->debug(__VA_ARGS__)
#define LOG_INFO(...)            ::SGLR::Log::GetLogger()->info(__VA_ARGS__)
#define LOG_TRACE(...)           ::SGLR::Log::GetLogger()->trace(__VA_ARGS__)
#define LOG_ASSERT(x, msg)	     if ((x)) {} else { LOG_FATAL("ASSERT - {}\n\t{}\n\tin file: {}\n\ton line: {}", #x, msg, __FILE__, __LINE__); LOG_BREAK  }

#define LOG_RELLOG(...)          ::SGLR::Log::GetLogger()->trace(__VA_ARGS__)

#else

#define LOG_FATAL(...)           (void)0
#define LOG_ERROR(...)           (void)0
#define LOG_WARN(...)            (void)0
#define LOG_DEBUG(...)           (void)0
#define LOG_INFO(...)            (void)0
#define LOG_TRACE(...)           (void)0
#define LOG_ASSERT(x, msg)		 (void)0

#define LOG_RELLOG(...)          ::SGLR::Log::GetLogger()->trace(__VA_ARGS__) // incase any info would want to be displayed whilst in release

#endif