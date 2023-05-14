#ifndef AN_ENGINE_CORE_CORE
#define AN_ENGINE_CORE_CORE

#include "Core/Logger.h"

#ifdef AN_ENABLE_ASSERTS
    #define AN_ASSERT(x, ...)                                                                      \
        {                                                                                          \
            if(!(x))                                                                               \
            {                                                                                      \
                AN_ERROR("Assertion failed: {0}", __VA_ARGS__);                                    \
                __debugbreak();                                                                    \
            }                                                                                      \
        }
#else
    #define AN_ASSERT(x, ...)
#endif

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

#endif // AN_ENGINE_CORE_CORE
