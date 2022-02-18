#ifndef ENGINE_AUDIO_AUDIO_H
#define ENGINE_AUDIO_AUDIO_H

#include <audio/types.h>

namespace xc {

class audio {
public:
    auto static create() -> std::shared_ptr<audio>;

    virtual auto play_sound(std::shared_ptr<sound> const& sound) -> void = 0;
};

}

#endif // ENGINE_AUDIO_AUDIO_H