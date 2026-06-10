// lumino_logger.cpp

#include "lumino_logger.h"

#include <iostream>
#include <mutex>

namespace Lumino
{

    std::string Logger::logLevelToString(LogLevel level)
    {
        switch (level)
        {
        case LogLevel::DEBUG:    return "DEBUG";
        case LogLevel::INFO:     return "INFO";
        case LogLevel::WARNING:  return "WARNING";
        case LogLevel::Error:      return "ERROR";
        case LogLevel::CRITICAL: return "CRITICAL";
        default:                 return "UNKNOWN";
        }
    }

    void ConsoleLogger::log(const std::string& message,
        LogLevel level)
    {
        std::lock_guard<std::mutex> guard(logMutex);

        const char* color = "\033[0m";

        switch (level)
        {
        case LogLevel::DEBUG:    color = "\033[36m"; break;   // Cyan
        case LogLevel::INFO:     color = "\033[32m"; break;   // Green
        case LogLevel::WARNING:  color = "\033[33m"; break;   // Yellow
        case LogLevel::Error:      color = "\033[31m"; break;   // Red
        case LogLevel::CRITICAL: color = "\033[1;31m"; break; // Bright Red
        }

        std::cout << color
            << "[" << logLevelToString(level) << "] "
            << message
            << "\033[0m"
            << std::endl;
    }

} // namespace Lumino