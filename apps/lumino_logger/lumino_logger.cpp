#include "lumino_logger.h"

#include <iostream>

namespace Lumino
{

    std::string Logger::logLevelToString(LogLevel level)
    {
        switch (level)
        {
        case LogLevel::DEBUG:
            return "DEBUG";

        case LogLevel::INFO:
            return "INFO";

        case LogLevel::WARNING:
            return "WARNING";

        case LogLevel::Error:
            return "ERROR";

        case LogLevel::CRITICAL:
            return "CRITICAL";

        default:
            return "UNKNOWN";
        }
    }

    void Logger::log(const std::string& message, LogLevel level)
    {
        std::lock_guard<std::mutex> lock(logMutex);

        std::cout
            << "[" << logLevelToString(level) << "] "
            << message
            << std::endl;
    }

    void ConsoleLogger::log(const std::string& message, LogLevel level)
    {
        std::lock_guard<std::mutex> lock(logMutex);

        std::cout
            << "[" << logLevelToString(level) << "] "
            << message
            << std::endl;
    }

} // namespace Lumino