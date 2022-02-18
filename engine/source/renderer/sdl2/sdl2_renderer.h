#ifndef ENGINE_RENDERER_SDL2_SDL2_RENDERER_H
#define ENGINE_RENDERER_SDL2_SDL2_RENDERER_H

#include <renderer/renderer.h>

namespace xc {

class sdl2_renderer final : public renderer {
    friend class renderer;

public:
    ~sdl2_renderer();

    auto create_texture(char const* path) -> resource_handle final;
    auto texture_size(resource_handle texture) -> vector2 final;

    auto set_camera(xc::vector2 const& camera) -> void final;

    auto clear_screen(color const& clear_color) -> void final;

    auto draw_texture(resource_handle          texture,
                      rectangle         const& rect) -> void final;
    auto draw_texture(resource_handle          texture,
                      rectangle         const& rect,
                      float                    rotation) -> void final;
    auto draw_texture(resource_handle          texture,
                      rectangle         const& rect,
                      float                    rotation,
                      color             const& tint) -> void final;

    auto present() -> void final;

private:
    sdl2_renderer(int logical_width, int logical_height);

    xc::vector2 _camera;
};

}

#endif // ENGINE_RENDERER_SDL2_SDL2_RENDERER_H