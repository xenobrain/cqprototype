// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "audio.h"

#ifdef AUDIO_MINIAUDIO
#include <audio/miniaudio/miniaudio_audio.h>
#endif // AUDIO_MINIAUDIO

namespace xc {

auto audio::create() -> std::shared_ptr<audio> {
#ifdef AUDIO_MINIAUDIO
    return std::shared_ptr<miniaudio_audio>{new miniaudio_audio{}};
#endif // AUDIO_MINIAUDIO
}

}