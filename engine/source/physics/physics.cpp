// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "physics.h"

namespace xc {

class collision_manifold {
public:
    collision_manifold(physics_body_component const& body_a, physics_body_component const& body_b)
        : _body_a{&body_a}, _body_b{&body_b} {
        solve_circle_circle();
    }

    std::vector<vector2> contact_points{};
    float collision_penetration = 0.f;
    vector2 collision_normal = vector2{0.f, 0.f};

private:
    auto solve_circle_circle() -> void {
        collision_normal = _body_b->position - _body_a->position;
        auto collision_distance_sq = length_sq(collision_normal);

        auto collision_radius = _body_a->radius + _body_b->radius;
        if (collision_distance_sq >= collision_radius * collision_radius) return;

        auto distance = std::sqrt(collision_distance_sq);

        if (distance == 0.f) {
            collision_penetration = _body_a->radius;
            collision_normal = vector2{1.f, 0.f};
            contact_points.emplace_back(_body_a->position);
        } else {
            collision_penetration = _body_a->radius;
            collision_normal /= distance;
            contact_points.emplace_back(collision_normal * _body_a->radius + _body_a->position);
        }
    }

    physics_body_component const* _body_a, *_body_b;
};

physics::physics(std::shared_ptr<xc::scene> scene) : _scene{std::move(scene)}, _gravity{0.f, 0.f} {}

physics::~physics() = default;

auto physics::create(std::shared_ptr<xc::scene> scene) -> std::shared_ptr<physics> {
    return std::shared_ptr<physics>{new physics{std::move(scene)}};
}

auto physics::create_body(vector2 const &position, float const radius, bool const is_dynamic) -> physics_body_component {
    auto body = physics_body_component{};

    auto mass = 1.f / PI * radius * radius; // * density = 1.0
    auto inertia_tensor = mass * radius * radius;

    body.radius = radius;
    body.position = position;
    body.inverse_mass = is_dynamic ? 1.f / mass : 0.f;
    body.inverse_inertia_tensor = 1.f / inertia_tensor;

    return body;
}

auto physics::add_force(entity_id entity, vector2 const &force) -> void {
    _scene->get_component<physics_body_component>(entity).force += force;
}

auto physics::tick(float const step) -> void {
    auto body_entities = _scene->view<physics_body_component>().entities;

    // Integrate forces
    for (auto entity: body_entities) {
        auto &body = _scene->get_component<physics_body_component>(entity);

        // Skip if the body is static
        if (body.inverse_mass == 0.f) continue;

        body.velocity += (_gravity + body.inverse_mass * body.force) * step;
        body.angular_velocity += body.inverse_inertia_tensor * body.torque * step;
    }

    // Find collisions
    for (auto i = std::size_t{0}; i < body_entities.size(); ++i) {
        auto entity_a = body_entities[i];
        auto& body_a = _scene->get_component<physics_body_component>(entity_a);

        for (auto j = std::size_t{1}; j < body_entities.size(); ++j) {
            auto entity_b = body_entities[j];
            auto& body_b = _scene->get_component<physics_body_component>(entity_b);

            auto new_manifold = collision_manifold(body_a, body_b);
            if (!new_manifold.contact_points.empty()) {
                _scene->add_component<collision_component>(entity_a, entity_b);
                _scene->add_component<collision_component>(entity_b, entity_a);
            }
        }
    }

    // Integrate velocities
    for (auto entity: body_entities) {
        auto &body = _scene->get_component<physics_body_component>(entity);

        body.position += body.velocity * step;
        body.rotation += body.angular_velocity * step;

        body.force = {0.f, 0.f};
        body.torque = 0.f;

        // Apply damping
        body.velocity *= 1.f / (1.f + body.damping * step);
        body.angular_velocity *= 1.f / (1.f + body.damping * step);
    }
}

}