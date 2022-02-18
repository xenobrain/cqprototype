// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "game.h"
#include "systems.h"
#include "constants.h"
#include "components.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

double current_time = 0;

double accumulator = 0;
double elapsed_time = 0;

game::game() = default;

game::~game() = default;

auto game::run() -> void {
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_arg(+[](void* t) { static_cast<game*>(t)->tick(); }, this, 0, true);
#else
    xc::event_system::get().on<quit_event>([this](auto&) { _running = false; } );
    while (_running) tick();
#endif // __EMSCRIPTEN__
}

auto game::initialize() -> void {
    _platform = xc::platform::create();
    _platform->create_window(WINDOW_WIDTH, WINDOW_HEIGHT);

    _renderer = xc::renderer::create(LOGICAL_WIDTH, LOGICAL_HEIGHT);
    _scene = xc::scene::create();

    _physics = xc::physics::create(_scene);
    _scripting = xc::scripting::create();

    _timer.reset();
    current_time = _timer.elapsed_ms();

    _player = create_player(_scene, _physics, _renderer);
    spawn_crystals(_scene, _physics, _renderer);
    spawn_gates(_scene, _physics, _renderer);

    _camera = create_camera(_scene, _player);

    _initialized = true;
}

auto game::tick() -> void {
    if (!_initialized) initialize();

    _platform->tick();

    _timer.reset();
    auto new_time = _timer.elapsed_ms();
    auto frame_time = new_time - current_time;
    if (frame_time > 0.25) frame_time = 0.25;
    current_time = new_time;

    accumulator += frame_time;

    while (accumulator >= TIME_STEP) {
        update_player(_scene, _player, TIME_STEP, _physics);

        _physics->tick(TIME_STEP);

        collect_crystals(_scene, _player);
        update_camera(_scene, _camera, _renderer);

        accumulator -= TIME_STEP;
        elapsed_time += TIME_STEP;
    }

    _renderer->clear_screen(xc::colors::CORNFLOWER_BLUE);

    draw_crystals(_scene, _renderer);
    draw_gates(_scene, _renderer);

    draw_player(_scene, _player, _renderer);

    _renderer->present();
}