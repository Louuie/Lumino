#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>
#include <mutex>

namespace Lumino
{

    enum class LogLevel
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        CRITICAL
    };

    class Logger
    {
    protected:
        std::mutex logMutex;

        std::string logLevelToString(LogLevel level);

    public:
        virtual ~Logger() = default;

        virtual void log(const std::string& message,
            LogLevel level);
    };

    class ConsoleLogger : public Logger
    {
    public:
        void log(const std::string& message,
            LogLevel level) override;
    };

} // namespace Lumino

#define LOG(logger, level, message) \
    (logger).log((message), (level), __FILE__, __LINE__)

#define LOG_DEBUG(logger, message) \
    LOG(logger, Lumino::LogLevel::DEBUG, message)

#define LOG_INFO(logger, message) \
    LOG(logger, Lumino::LogLevel::INFO, message)

#define LOG_WARNING(logger, message) \
    LOG(logger, Lumino::LogLevel::WARNING, message)

#define LOG_ERROR(logger, message) \
    LOG(logger, Lumino::LogLevel::ERROR, message)

#define LOG_CRITICAL(logger, message) \
    LOG(logger, Lumino::LogLevel::CRITICAL, message)

#endif // LOGGER_H_