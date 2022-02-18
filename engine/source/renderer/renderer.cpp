// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "renderer.h"

#ifdef RENDERER_SDL2
#include <renderer/sdl2/sdl2_renderer.h>
#endif
#ifdef RENDERER_GLES2
#include <renderer/gl/gl_renderer.h>
#endif
#ifdef RENDERER_VULKAN
#include <renderer/vulkan/vulkan_renderer.h>
#endif

namespace xc {

auto renderer::create(int const logical_width, int const logical_height) -> std::shared_ptr<renderer> {
#ifdef RENDERER_SDL2
    return std::shared_ptr<sdl2_renderer>{new sdl2_renderer{logical_width, logical_height}};
#endif
#ifdef RENDERER_GLES2
    return std::shared_ptr<gl_renderer>{new gl_renderer{logical_width, logical_height}};
#endif
#ifdef RENDERER_VULKAN
    return std::shared_ptr<vulkan_renderer>{new vulkan_renderer{logical_width, logical_height}};
#endif
}

}