#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

// Window
auto static constexpr LOGICAL_SCALE = 1;
auto static constexpr LOGICAL_WIDTH = 1280;
auto static constexpr LOGICAL_HEIGHT = 720;

auto static constexpr WINDOW_WIDTH = LOGICAL_WIDTH * LOGICAL_SCALE;
auto static constexpr WINDOW_HEIGHT = LOGICAL_HEIGHT * LOGICAL_SCALE;

auto static constexpr CENTER_X = LOGICAL_WIDTH / 2.f;
auto static constexpr CENTER_Y = LOGICAL_HEIGHT / 2.f;

// Time
auto static TIME_STEP = 1.f / 60.f;

// Map
auto static MAP_WIDTH = 2000.f;
auto static MAP_HEIGHT = 2000.f;
auto static MAP_CELL_SIZE = 64.f;

// Player
auto static constexpr PLAYER_TEXTURE_PATH = "assets/player.png";
auto static constexpr PLAYER_THRUST = 10'000.f;
auto static constexpr PLAYER_WIDTH = 32.f;
auto static constexpr PLAYER_HEIGHT = 32.f;
auto static constexpr PLAYER_RADIUS = PLAYER_WIDTH / 2.f; // slightly smaller than the rect-should match with sprite

// Crystals
auto static constexpr CRYSTAL_TEXTURE_PATH = "assets/crystal.png";
auto static constexpr CRYSTAL_SPAWN_PROBABILITY = 28;
auto static constexpr CRYSTAL_WIDTH = 16.f;
auto static constexpr CRYSTAL_HEIGHT = 16.f;
auto static constexpr CRYSTAL_RADIUS = xc::radius_of_rectangle(CRYSTAL_WIDTH, CRYSTAL_HEIGHT); // fully encloses rect

// Gate
auto static constexpr GATE_TEXTURE_PATH = "assets/gate.png";
auto static constexpr GATE_SPAWN_PROBABILITY = 128;
auto static constexpr GATE_WIDTH = 48.f;
auto static constexpr GATE_HEIGHT = 48.f;
auto static constexpr GATE_RADIUS = GATE_WIDTH / 2.f;

#endif // GAME_CONSTANTS_H