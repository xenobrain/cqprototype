#ifndef ENGINE_AUDIO_MINIAUDIO_MINIAUDIO_AUDIO_H
#define ENGINE_AUDIO_MINIAUDIO_MINIAUDIO_AUDIO_H

#include <audio/audio.h>
#include <audio/miniaudio/types.h>

namespace xc {

class miniaudio_audio final : public audio {
    friend class audio;

public:
    ~miniaudio_audio();

    auto play_sound(std::shared_ptr<sound> const& sound) -> void final;

private:
    miniaudio_audio();
};

}
#endif // ENGINE_AUDIO_MINIAUDIO_MINIAUDIO_AUDIO_H
