#ifndef GAME_COMPONENTS_H
#define GAME_COMPONENTS_H

#include <engine.h>

struct gate_tag {};
struct player_tag {};
struct crystal_tag {};

struct transform_component {
    xc::vector2 position;
};

struct texture_component {
    xc::resource_handle resource;
    float width, height;
};

struct camera_component {
    xc::entity_id target;
    xc::vector2 offset;
};

struct collector_component {
    std::uint32_t count;
};

struct collectable_component {};

#endif // GAME_COMPONENTS_H