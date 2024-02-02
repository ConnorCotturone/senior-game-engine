// jacob curlin
// logging.h
// 01/16/2023

#ifndef LOGGING_H
#define LOGGING_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <vector>
#include <memory>

namespace cgx::utility
{
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

    #define CGX_DEFAULT_LOGGER_NAME "core"

    #define CGX_TRACE(...)      if (spdlog::get(CGX_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(CGX_DEFAULT_LOGGER_NAME)->trace(__VA_ARGS__);}
    #define CGX_DEBUG(...)      if (spdlog::get(CGX_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(CGX_DEFAULT_LOGGER_NAME)->debug(__VA_ARGS__);}
    #define CGX_INFO(...)       if (spdlog::get(CGX_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(CGX_DEFAULT_LOGGER_NAME)->info(__VA_ARGS__);}
    #define CGX_WARN(...)       if (spdlog::get(CGX_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(CGX_DEFAULT_LOGGER_NAME)->warn(__VA_ARGS__);}
    #define CGX_ERROR(...)      if (spdlog::get(CGX_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(CGX_DEFAULT_LOGGER_NAME)->error(__VA_ARGS__);}
    #define CGX_CRITICAL(...)   if (spdlog::get(CGX_DEFAULT_LOGGER_NAME) != nullptr) {spdlog::get(CGX_DEFAULT_LOGGER_NAME)->critical(__VA_ARGS__);}

    // x : condition being asserted  |  msg : message to print upon failure of assertion
    //  {} : (do nothing)   |  
    #define CGX_ASSERT(x, msg) if ((x)) {} else {CGX_CRITICAL("ASSERT - {}\n\t{}\n\tin file: {}\n\ton line: {}", #x, msg, __FILE__, __LINE__); }  

}

#endif // LOGGING_H