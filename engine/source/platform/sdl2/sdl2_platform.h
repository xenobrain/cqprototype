#ifndef ENGINE_PLATFORM_SDL2_SDL2_PLATFORM_H
#define ENGINE_PLATFORM_SDL2_SDL2_PLATFORM_H

#include <platform/platform.h>

namespace xc {

class sdl2_platform final : public platform {
    friend class platform;

public:
    ~sdl2_platform();

    auto create_window(int width, int height) -> void final;
    auto static window_handle() -> void*;

    auto tick() -> void final;

private:
    sdl2_platform();
};

}

#endif // ENGINE_PLATFORM_SDL2_SDL2_PLATFORM_H