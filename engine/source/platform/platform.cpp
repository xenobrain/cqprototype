// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "platform.h"

#ifdef PLATFORM_SDL2
#include <platform/sdl2/sdl2_platform.h>
#endif

namespace xc {

auto platform::create() -> std::shared_ptr<platform> {
#ifdef PLATFORM_SDL2
    return std::shared_ptr<sdl2_platform>{new sdl2_platform{}};
#endif
}

}