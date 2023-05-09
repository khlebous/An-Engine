#include "Core/Logger.h"

#include "spdlog/sinks/stdout_color_sinks.h"

using namespace an::core;

std::shared_ptr<spdlog::logger> an::core::Logger::s_logger;

//--------------------------------------------------------------------------------------------------
void Logger::init()
{
    s_logger = spdlog::stdout_color_mt("AN ENGINE");
    s_logger->set_level(spdlog::level::trace);
    s_logger->set_pattern("%^[%T] [%=7!l] %v%$");
}

//--------------------------------------------------------------------------------------------------
std::shared_ptr<spdlog::logger> &Logger::getLogger()
{
    return s_logger;
}
