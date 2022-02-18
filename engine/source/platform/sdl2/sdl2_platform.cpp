#include "sdl2_platform.h"
#include <core/events.h>
#include <core/input.h>

#include <SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

namespace xc {

SDL_Window* sdl_window = nullptr;

sdl2_platform::sdl2_platform() {
    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) throw std::runtime_error(SDL_GetError());
}

sdl2_platform::~sdl2_platform() {
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

auto sdl2_platform::create_window(int width, int height) -> void {
    auto constexpr position = SDL_WINDOWPOS_CENTERED;
    auto constexpr flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL;

    sdl_window = SDL_CreateWindow("Hello SDL", position, position, width, height, flags);
    if (!sdl_window) throw std::runtime_error(SDL_GetError());
}

auto sdl2_platform::window_handle() -> void * {
    return static_cast<void*>(sdl_window);
}


auto sdl2_platform::tick() -> void {
    auto event = SDL_Event{};
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
#ifdef __EMSCRIPTEN__
            emscripten_cancel_main_loop();
#else
            event_system::get().publish<quit_event>();
#endif
        }
    }
}

auto constexpr translate_key(SDL_Scancode code) -> key {
    switch (code) {
        case SDL_SCANCODE_W: return key::eW;
        case SDL_SCANCODE_A: return key::eA;
        case SDL_SCANCODE_S: return key::eS;
        case SDL_SCANCODE_D: return key::eD;
        default: return key::eUnknown;
    }
}

auto constexpr translate_key(key code) -> SDL_Scancode {
    switch (code) {
        case key::eW: return SDL_SCANCODE_W;
        case key::eA: return SDL_SCANCODE_A;
        case key::eS: return SDL_SCANCODE_S;
        case key::eD: return SDL_SCANCODE_D;
        default: return SDL_SCANCODE_UNKNOWN;
    }
}

auto input::is_key_down(key code) -> bool {
    auto* state = SDL_GetKeyboardState(nullptr);
    return state[translate_key(code)];
}

auto input::mouse_x() -> float {
    auto x = 0, y = 0;
    SDL_GetMouseState(&x, nullptr);
    return static_cast<float>(x);
}

auto input::mouse_y() -> float {
    auto x = 0, y = 0;
    SDL_GetMouseState(nullptr, &y);
    return static_cast<float>(y);
}
}