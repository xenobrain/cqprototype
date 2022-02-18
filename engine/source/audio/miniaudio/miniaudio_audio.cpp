// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "miniaudio_audio.h"

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>

namespace xc {

ma_engine engine;

miniaudio_audio::miniaudio_audio() {
    if (ma_engine_init(nullptr, &engine) != MA_SUCCESS) throw std::runtime_error("Could not initialize audio");
}

miniaudio_audio::~miniaudio_audio() {
    ma_engine_uninit(&engine);
}

auto miniaudio_audio::play_sound(std::shared_ptr<sound> const& sound) -> void {
    //ma_engine_play_sound(&engine, sound.get())
}

}