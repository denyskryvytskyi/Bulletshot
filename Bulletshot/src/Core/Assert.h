#pragma once

#ifdef DEBUG
    #define ASSERTIONS_ENABLED
    #define DEBUGBREAK() __debugbreak()
#else
    #define DEBUGBREAK()
#endif

#ifdef ASSERTIONS_ENABLED
    #define ASSERT(expr) if (expr) {} \
        else \
        { \
            DEBUGBREAK(); \
        }
#else
    #define ASSERT(expr)
#endif