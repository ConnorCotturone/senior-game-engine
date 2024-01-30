// jacob curlin
// logging.h
// 01/16/2023

#ifndef LOGGING_H
#define LOGGING_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <vector>
#include <memory>

class LoggingHandler {

public:
    static void Initialize();
    static void Shutdown();

    inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
    inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

private:
    static std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> s_ConsoleSink;
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;

};

#define PHX_DEFAULT_LOGGER_NAME "core"

#define PHX_TRACE(...)      if (spdlog::get(PHX_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(PHX_DEFAULT_LOGGER_NAME)->trace(__VA_ARGS__);}
#define PHX_DEBUG(...)      if (spdlog::get(PHX_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(PHX_DEFAULT_LOGGER_NAME)->debug(__VA_ARGS__);}
#define PHX_INFO(...)       if (spdlog::get(PHX_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(PHX_DEFAULT_LOGGER_NAME)->info(__VA_ARGS__);}
#define PHX_WARN(...)       if (spdlog::get(PHX_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(PHX_DEFAULT_LOGGER_NAME)->warn(__VA_ARGS__);}
#define PHX_ERROR(...)      if (spdlog::get(PHX_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(PHX_DEFAULT_LOGGER_NAME)->error(__VA_ARGS__);}
#define PHX_CRITICAL(...)   if (spdlog::get(PHX_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(PHX_DEFAULT_LOGGER_NAME)->critical(__VA_ARGS__);}

// x : condition being asserted  |  msg : message to print upon failure of assertion
//  {} : (do nothing)   |  
#define PHX_ASSERT(x, msg) if ((x)) {} else {PHX_CRITICAL("ASSERT - {}\n\t{}\n\tin file: {}\n\ton line: {}", #x, msg, __FILE__, __LINE__); }  

#endif // LOGGING_H