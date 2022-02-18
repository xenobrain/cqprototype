#ifndef ENGINE_PHYSICS_TYPES_H
#define ENGINE_PHYSICS_TYPES_H

#include <core/types.h>
#include <scene/types.h>

struct collision_component {
    xc::entity_id collider;
};

struct physics_body_component {
    xc::vector2 position, velocity, force;
    float angular_velocity, rotation, torque;
    float inverse_mass, inverse_inertia_tensor, damping;
    float radius;
};

#endif // ENGINE_PHYSICS_TYPES_H