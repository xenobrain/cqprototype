#include "vulkan_renderer.h"

namespace xc {

vulkan_renderer::vulkan_renderer(int logical_width, int logical_height) {

}

vulkan_renderer::~vulkan_renderer() {

}

auto vulkan_renderer::create_texture(char const* path) -> resource_handle {

}

auto vulkan_renderer::texture_size(resource_handle texture) -> vector2 {

}

auto vulkan_renderer::set_camera(vector2 const& camera) -> void {

}

auto vulkan_renderer::clear_screen(color const& clear_color) -> void {

}

auto vulkan_renderer::draw_texture(resource_handle          texture,
                          rectangle         const& rect) -> void {

};

auto vulkan_renderer::draw_texture(resource_handle          texture,
                          rectangle         const& rect,
                          float                    rotation) -> void {

}

auto vulkan_renderer::draw_texture(resource_handle          texture,
                          rectangle         const& rect,
                          float                    rotation,
                          color             const& tint) -> void {

}

auto vulkan_renderer:: present() -> void {

}

}