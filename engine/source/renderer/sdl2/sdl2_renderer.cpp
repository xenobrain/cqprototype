// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "sdl2_renderer.h"
#include <platform/sdl2/sdl2_platform.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <SDL.h>

namespace xc {

SDL_Renderer* sdl_renderer = nullptr;

std::vector<SDL_Texture*> texture_cache;

sdl2_renderer::sdl2_renderer(int const logical_width, int const logical_height) {
    SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");
    auto constexpr flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;

    sdl_renderer = SDL_CreateRenderer(reinterpret_cast<SDL_Window*>(sdl2_platform::window_handle()), -1, flags);
    if (!sdl_renderer) throw std::runtime_error(SDL_GetError());

    SDL_RenderSetLogicalSize(sdl_renderer, logical_width, logical_height);
    SDL_RenderSetIntegerScale(sdl_renderer, SDL_TRUE);

    _camera = xc::vector2{0.f, 0.f};
}

sdl2_renderer::~sdl2_renderer() {
    SDL_DestroyRenderer(sdl_renderer);
}

auto sdl2_renderer::create_texture(const char *path) -> resource_handle {
    auto width = 0, height = 0, source_format = 0;

    auto* image = stbi_load(path, &width, &height, &source_format, STBI_rgb_alpha);
    if (!image) throw std::runtime_error(stbi_failure_reason());

    auto* surface = SDL_CreateRGBSurfaceWithFormatFrom(image, width, height, 32, width * 4, SDL_PIXELFORMAT_RGBA32);
    if (!surface) throw std::runtime_error(SDL_GetError());

    auto* texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);
    if (!texture) throw std::runtime_error(SDL_GetError());

    texture_cache.push_back(texture);

    stbi_image_free(image);
    SDL_FreeSurface(surface);

    return texture_cache.size() - 1;
}

auto sdl2_renderer::texture_size(resource_handle texture) -> vector2 {
    auto x = 0, y = 0;
    if (!SDL_QueryTexture(texture_cache[texture], nullptr, nullptr, &x, &y)) throw std::runtime_error(SDL_GetError());

    return vector2{static_cast<float>(x), static_cast<float>(y)};
}

auto sdl2_renderer::set_camera(const xc::vector2 &camera) -> void {
    _camera = camera;
}

auto sdl2_renderer::clear_screen(color const& clear_color) -> void {
    SDL_SetRenderDrawColor(sdl_renderer, clear_color.r, clear_color.g, clear_color.b, clear_color.a);
    SDL_RenderClear(sdl_renderer);
}

auto sdl2_renderer::draw_texture(resource_handle          texture,
                  rectangle         const& rect) -> void {
    draw_texture(texture, rect, 0.f, colors::WHITE);
}

auto sdl2_renderer::draw_texture(resource_handle          texture,
                  rectangle         const& rect,
                  float                    rotation) -> void {
    draw_texture(texture, rect, rotation, colors::WHITE);
}

auto sdl2_renderer::draw_texture(resource_handle          texture,
                  rectangle         const& rect,
                  float                    rotation,
                  color             const& tint) -> void {
    auto destination_rect = SDL_FRect{rect.x - _camera.x, rect.y - _camera.y, rect.w, rect.h};
    auto* sdl_texture = texture_cache[texture];

    //SDL_SetTextureAlphaMod(sdl_texture, tint.a);
    SDL_SetTextureColorMod(sdl_texture, tint.r, tint.g, tint.b);

    SDL_RenderCopyExF(sdl_renderer,         // renderer
                      sdl_texture,          // SDL_Texture*
                      {},                   // source FRect*
                      &destination_rect,    // destination FRect*
                      rotation,             // rotation angle in degrees
                      {},                   // rotation center
                      SDL_FLIP_NONE);       // flip
}

auto sdl2_renderer::present() -> void {
    SDL_RenderPresent(sdl_renderer);
}

}