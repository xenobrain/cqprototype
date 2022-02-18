// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "scene.h"

namespace xc {

scene::scene() = default;

scene::~scene() = default;

auto scene::create() -> std::shared_ptr<scene> {
    return std::shared_ptr<scene>{new scene{}};
}

}