#include "systems.h"

#include <random>

#include "constants.h"
#include "components.h"

auto collect_crystals(std::shared_ptr<xc::scene>& scene, xc::entity_id player) -> void {
    // collision component keeps getting added every frame and the collider entity isn't getting removed
    if (scene->has_component<collision_component>(player)) {
        // Get the other entity
        auto collider_entity = scene->get_component<collision_component>(player).collider;

        // Return if it's not a crystal
        if (!scene->has_component<collectable_component>(collider_entity)) return;

        // Increment the player's collection counter
        auto& count = scene->get_component<collector_component>(player).count;
        ++count;

        // Remove the collision from the player
        scene->remove_component<collision_component>(player);

        // Remove the crystal entity and therefore all it's components
        scene->remove_entity(collider_entity);
    }
}

auto create_player(std::shared_ptr<xc::scene>& scene, std::shared_ptr<xc::physics>& physics, std::shared_ptr<xc::renderer>& renderer) -> xc::entity_id {
    auto texture = renderer->create_texture(PLAYER_TEXTURE_PATH);
    auto player = scene->create_entity();

    auto& transform = scene->add_component<transform_component>(player, xc::vector2{
        CENTER_X, CENTER_Y});

    scene->add_component<collector_component>(player, 0u);

    scene->add_component<texture_component>(player, texture, PLAYER_WIDTH, PLAYER_HEIGHT);

    auto body = physics->create_body(transform.position, PLAYER_RADIUS, true);
    scene->add_component<physics_body_component>(player, body);
    // TODO: cap the maximum velocity

    return player;
}

auto update_player(std::shared_ptr<xc::scene>& scene, xc::entity_id player, float const step, std::shared_ptr<xc::physics>& physics) -> void {
    auto& body  = scene->get_component<physics_body_component>(player);
    auto& position = scene->get_component<transform_component>(player).position = body.position; // sync transform

    if (xc::input::is_key_down(xc::key::eW)) physics->add_force(player, {0.f, -PLAYER_THRUST});
    if (xc::input::is_key_down(xc::key::eA)) physics->add_force(player, {-PLAYER_THRUST, 0});
    if (xc::input::is_key_down(xc::key::eS)) physics->add_force(player, {0, PLAYER_THRUST});
    if (xc::input::is_key_down(xc::key::eD)) physics->add_force(player, {PLAYER_THRUST, 0});
}

auto draw_player(std::shared_ptr<xc::scene>& scene, xc::entity_id player, std::shared_ptr<xc::renderer>& renderer) -> void {
    auto& texture = scene->get_component<texture_component>(player);

    // get transform and sync with physics
    auto& position = scene->get_component<transform_component>(player).position;

    renderer->draw_texture(texture.resource, {position.x, position.y, texture.width, texture.height});
}

auto spawn_crystals(std::shared_ptr<xc::scene>& scene, std::shared_ptr<xc::physics>& physics, std::shared_ptr<xc::renderer>& renderer) -> void {
    auto rng = std::default_random_engine{};
    auto spawn_probability = std::uniform_int_distribution<int>(0, CRYSTAL_SPAWN_PROBABILITY);
    auto cell_x_distribution = std::uniform_int_distribution<float>(0.f, MAP_WIDTH / MAP_CELL_SIZE);
    auto cell_y_distribution = std::uniform_int_distribution<float>(0.f, MAP_HEIGHT / MAP_CELL_SIZE);
    auto cell_offset_distribution = std::uniform_int_distribution<float>(0, MAP_CELL_SIZE);

    auto texture = renderer->create_texture(CRYSTAL_TEXTURE_PATH);

    for (auto i = 0; i < (MAP_WIDTH / MAP_CELL_SIZE) * (MAP_HEIGHT / MAP_CELL_SIZE); ++i) {
        if (spawn_probability(rng) % CRYSTAL_SPAWN_PROBABILITY != 0) continue;

        auto position = xc::vector2{
            cell_x_distribution(rng) * MAP_CELL_SIZE + cell_offset_distribution(rng),
            cell_y_distribution(rng) * MAP_CELL_SIZE + cell_offset_distribution(rng)
        };

        auto entity = scene->create_entity();
        scene->add_component<crystal_tag>(entity);
        scene->add_component<collectable_component>(entity);
        scene->add_component<transform_component>(entity, position);
        scene->add_component<texture_component>(entity, texture, CRYSTAL_WIDTH, CRYSTAL_HEIGHT);

        auto body = physics->create_body(position, CRYSTAL_RADIUS);
        scene->add_component<physics_body_component>(entity, body);
    }
}

auto draw_crystals(std::shared_ptr<xc::scene>& scene, std::shared_ptr<xc::renderer>& renderer) -> void {
    auto crystals = scene->view<crystal_tag, texture_component, transform_component>().entities;

    for (auto const& crystal : crystals) {
        auto& texture = scene->get_component<texture_component>(crystal);
        auto& position = scene->get_component<transform_component>(crystal).position;

        renderer->draw_texture(texture.resource, {position.x, position.y, texture.width, texture.height});
    }
}

auto create_camera(std::shared_ptr<xc::scene>& scene, xc::entity_id target) -> xc::entity_id {
    auto camera = scene->create_entity();
    scene->add_component<camera_component>(camera, target, xc::vector2{CENTER_X, CENTER_Y});
    scene->add_component<transform_component>(camera, xc::vector2{-CENTER_X, -CENTER_Y});

    return camera;
}

auto spawn_gates(std::shared_ptr<xc::scene>& scene, std::shared_ptr<xc::physics>& physics, std::shared_ptr<xc::renderer>& renderer) -> void {
    auto rng = std::default_random_engine{};
    auto spawn_probability = std::uniform_int_distribution<int>(0, GATE_SPAWN_PROBABILITY);
    auto cell_x_distribution = std::uniform_int_distribution<float>(0.f, MAP_WIDTH / MAP_CELL_SIZE);
    auto cell_y_distribution = std::uniform_int_distribution<float>(0.f, MAP_HEIGHT / MAP_CELL_SIZE);
    auto cell_offset_distribution = std::uniform_int_distribution<float>(0, MAP_CELL_SIZE);

    auto texture = renderer->create_texture(GATE_TEXTURE_PATH);

    for (auto i = 0; i < (MAP_WIDTH / MAP_CELL_SIZE) * (MAP_HEIGHT / MAP_CELL_SIZE); ++i) {
        if (spawn_probability(rng) % GATE_SPAWN_PROBABILITY != 0) continue;

        auto position = xc::vector2{
                cell_x_distribution(rng) * MAP_CELL_SIZE + cell_offset_distribution(rng),
                cell_y_distribution(rng) * MAP_CELL_SIZE + cell_offset_distribution(rng)
        };

        auto entity = scene->create_entity();
        scene->add_component<gate_tag>(entity);
        scene->add_component<transform_component>(entity, position);
        scene->add_component<texture_component>(entity, texture, GATE_WIDTH, GATE_HEIGHT);

        auto body = physics->create_body(position, GATE_RADIUS);
        scene->add_component<physics_body_component>(entity, body);
    }
}

auto draw_gates(std::shared_ptr<xc::scene>& scene, std::shared_ptr<xc::renderer>& renderer) -> void {
    auto gate_entities = scene->view<gate_tag, texture_component, transform_component>().entities;

    for (auto const& gate_entity : gate_entities) {
        auto& texture = scene->get_component<texture_component>(gate_entity);
        auto& position = scene->get_component<transform_component>(gate_entity).position;

        renderer->draw_texture(texture.resource, {position.x, position.y, texture.width, texture.height});
    }
}

auto update_camera(std::shared_ptr<xc::scene>& scene, xc::entity_id camera_entity, std::shared_ptr<xc::renderer>& renderer) -> void {
    auto& camera = scene->get_component<camera_component>(camera_entity);
    auto& camera_position = scene->get_component<transform_component>(camera_entity);

    auto& target_position = scene->get_component<transform_component>(camera.target).position;
    camera_position.position = target_position - camera.offset;

    renderer->set_camera(scene->get_component<transform_component>(camera_entity).position);
}