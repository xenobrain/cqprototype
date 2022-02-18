#ifndef ENIGINE_RENDERER_GLES2_GLES2_RENDERER_H
#define ENIGINE_RENDERER_GLES2_GLES2_RENDERER_H

#include <renderer/renderer.h>

namespace xc {

class gl_renderer : public renderer {
    friend class renderer;

public:
    ~gl_renderer();

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
    gl_renderer(int logical_width, int logical_height);

    auto resize(int width, int height) -> void;
};
}

#endif // ENIGINE_RENDERER_GLES2_GLES2_RENDERER_H