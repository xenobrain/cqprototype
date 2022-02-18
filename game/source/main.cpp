// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "game.h"

auto main(int, char**) -> int {
    try {
        auto app = game{};
        app.run();

    } catch (std::exception const& exception) {
        log_error("%s", exception.what());
        return EXIT_FAILURE;
    } catch (...) {
        log_error("%s", "Caught unknown error");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*
 * Game Design
 * Collect all the crystals to open the gate
 * Avoid the enemies
 * Enemies spawn from portals which you can destroy
 * Levels have fixed structures creating a somewhat maze-like level
 * The location of the exit is unknown the the player until it appears
 */