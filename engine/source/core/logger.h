#ifndef ENGINE_CORE_LOGGER_H
#define ENGINE_CORE_LOGGER_H

#include <SDL.h>

enum class log_severity { Info, Warn, Error, Verbose};

template<typename... Args> auto inline log_output(log_severity severity, char const* message, Args&& ...args) -> void {
    switch (severity) {
        case log_severity::Info:
            SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, message, args...);
            break;
        case log_severity::Warn:
            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, message, args...);
            break;
        case log_severity::Error:
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, message, args...);
            break;
        case log_severity::Verbose:
            SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, message, args...);
            break;
    }
}

#define log_info(fmt, ...) do { \
log_output(log_severity::Info, "%s:%d \n\t%s()\n\t\t" fmt, __FILE__, __LINE__, __func__, __VA_ARGS__); \
} while (0)

#define log_warn(fmt, ...) do { \
log_output(log_severity::Warn, "%s:%d \n\t%s()\n\t\t" fmt, __FILE__, __LINE__, __func__, __VA_ARGS__); \
} while (0)

#define log_error(fmt, ...) do { \
log_output(log_severity::Error, "%s:%d \n\t%s()\n\t\t" fmt, __FILE__, __LINE__, __func__, __VA_ARGS__); \
} while (0)

#define log_verbose(fmt, ...) do { \
log_output(log_severity::Verbose, "%s:%d \n\t%s()\n\t\t" fmt, __FILE__, __LINE__, __func__, __VA_ARGS__); \
} while (0)

#endif // ENGINE_CORE_LOGGER_H