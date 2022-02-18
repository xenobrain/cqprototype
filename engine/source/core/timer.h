#ifndef ENGINE_CORE_TIMER_H
#define ENGINE_CORE_TIMER_H

#include <chrono>
#include <SDL.h>
namespace xc {

class timer {
public:
    timer() {
        reset();
    }

    auto reset() -> void {}

    auto elapsed_ms() -> double {
        return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - _start).count();
    }

private:
    std::uint64_t _clock_frequency;
    std::chrono::time_point<std::chrono::high_resolution_clock> _start;
};

}

#endif // ENGINE_CORE_TIMER_H