#pragma once

#ifdef AN_EXPORTS
    #define AN_API __declspec(dllexport)
#else
    #define AN_API __declspec(dllimport)
#endif
