#ifndef ENGINE_RENDERER_RENDERER_H
#define ENGINE_RENDERER_RENDERER_H

#include <renderer/types.h>

namespace xc {

class renderer {
public:
    auto static create(int logical_width, int logical_height) -> std::shared_ptr<renderer>;

    virtual auto create_texture(char const* path) -> resource_handle = 0;
    virtual auto texture_size(resource_handle texture) -> vector2 = 0;

    virtual auto set_camera(vector2 const& camera) -> void = 0;

    virtual auto clear_screen(color const& clear_color) -> void = 0;

    virtual auto draw_texture(resource_handle          texture,
                              rectangle         const& rect) -> void = 0;
    virtual auto draw_texture(resource_handle          texture,
                              rectangle         const& rect,
                              float                    rotation) -> void = 0;
    virtual auto draw_texture(resource_handle          texture,
                              rectangle         const& rect,
                              float                    rotation,
                              color             const& tint) -> void = 0;

    virtual auto present() -> void = 0;
};

}

#endif // ENGINE_RENDERER_RENDERER_H