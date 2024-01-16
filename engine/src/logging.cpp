// jacob curlin
// logging.cpp
// 01/16/2023

#include "../include/logging.h"

std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> LoggingHandler::s_ConsoleSink;
std::shared_ptr<spdlog::logger> LoggingHandler::s_CoreLogger; 
std::shared_ptr<spdlog::logger> LoggingHandler::s_ClientLogger;

void LoggingHandler::Initialize()
{
    s_ConsoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    s_ConsoleSink->set_pattern("%^[%Y-%m-%d %H:%M:%S.%e] %n: %v%$");

    std::vector<spdlog::sink_ptr> sinks { s_ConsoleSink };

    s_CoreLogger = std::make_shared<spdlog::logger>("EngineLogger", sinks.begin(), sinks.end());
    s_CoreLogger->set_level(spdlog::level::trace);
    s_CoreLogger->flush_on(spdlog::level::trace);     // flush on receipt of every trace-level log message

    spdlog::register_logger(s_CoreLogger);

    s_ClientLogger = std::make_shared<spdlog::logger>("ClientLogger", sinks.begin(), sinks.end());
    s_ClientLogger->set_level(spdlog::level::trace);
    s_ClientLogger->flush_on(spdlog::level::trace);     // flush on receipt of every trace-level log message

    spdlog::register_logger(s_ClientLogger);

}

void LoggingHandler::Shutdown()
{
    spdlog::shutdown();
}