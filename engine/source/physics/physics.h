#ifndef ENGINE_PHYSICS_PHYSICS_H
#define ENGINE_PHYSICS_PHYSICS_H

#include <physics/types.h>
#include <scene/scene.h>

namespace xc {

class physics {
public:
    ~physics();

    auto static create(std::shared_ptr<xc::scene> scene) -> std::shared_ptr<physics>;

    auto create_body(vector2 const& position, float radius, bool is_dynamic = true) -> physics_body_component;

    auto add_force(entity_id entity, vector2 const& force) -> void;

    auto tick(float step) -> void;

private:
    physics(std::shared_ptr<xc::scene> scene);

    vector2 _gravity;
    std::shared_ptr<xc::scene> _scene;
};

}

#endif // ENGINE_PHYSICS_PHYSICS_H