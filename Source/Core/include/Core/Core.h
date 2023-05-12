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