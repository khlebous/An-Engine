#ifndef AN_CORE_LOGGER_H
#define AN_CORE_LOGGER_H

#include "spdlog/spdlog.h"

namespace an::core
{

class Logger
{
  public:
    static void init();
    static std::shared_ptr<spdlog::logger> &getLogger();

  private:
    static std::shared_ptr<spdlog::logger> s_logger;
};

} // namespace an::core

#ifdef AN_ENABLE_ASSERTS
    #define AN_TRACE(...) ::an::core::Logger::getLogger()->trace(__VA_ARGS__)
    #define AN_INFO(...)  ::an::core::Logger::getLogger()->info(__VA_ARGS__)
    #define AN_WARN(...)  ::an::core::Logger::getLogger()->warn(__VA_ARGS__)
    #define AN_ERROR(...) ::an::core::Logger::getLogger()->error(__VA_ARGS__)
#else
    #define AN_TRACE(...)
    #define AN_INFO(...)
    #define AN_WARN(...)
    #define AN_ERROR(...)
#endif

#endif // AN_CORE_LOGGER_H
