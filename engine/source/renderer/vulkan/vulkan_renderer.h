#ifndef ENGINE_RENDERER_VULKAN_VULKAN_RENDERER_H
#define ENGINE_RENDERER_VULKAN_VULKAN_RENDERER_H

#include <renderer/renderer.h>

namespace xc {

class vulkan_renderer : public renderer {
    friend class renderer;

public:
    ~vulkan_renderer();

    auto create_texture(char const* path) -> resource_handle final;
    auto texture_size(resource_handle texture) -> vector2 final;

    auto set_camera(vector2 const& camera) -> void final;

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
    vulkan_renderer(int logical_width, int logical_height);
};

}

#endif // ENGINE_RENDERER_VULKAN_VULKAN_RENDERER_H