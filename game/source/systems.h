#ifndef GAME_SYSTEMS_H
#define GAME_SYSTEMS_H

#include <engine.h>

auto create_player(std::shared_ptr<xc::scene>& scene, std::shared_ptr<xc::physics>& physics, std::shared_ptr<xc::renderer>& renderer) -> xc::entity_id;
auto update_player(std::shared_ptr<xc::scene>& scene, xc::entity_id player, float step, std::shared_ptr<xc::physics>& physics) -> void;
auto collect_crystals(std::shared_ptr<xc::scene>& scene, xc::entity_id player) -> void;
auto draw_player(std::shared_ptr<xc::scene>& scene, xc::entity_id player, std::shared_ptr<xc::renderer>& renderer) -> void;

auto spawn_crystals(std::shared_ptr<xc::scene>& scene, std::shared_ptr<xc::physics>& physics, std::shared_ptr<xc::renderer>& renderer) -> void;
auto draw_crystals(std::shared_ptr<xc::scene>& scene, std::shared_ptr<xc::renderer>& renderer) -> void;

auto spawn_gates(std::shared_ptr<xc::scene>& scene, std::shared_ptr<xc::physics>& physics, std::shared_ptr<xc::renderer>& renderer) -> void;
auto draw_gates(std::shared_ptr<xc::scene>& scene, std::shared_ptr<xc::renderer>& renderer) -> void;

auto create_camera(std::shared_ptr<xc::scene>& scene, xc::entity_id target) -> xc::entity_id;
auto update_camera(std::shared_ptr<xc::scene>& scene, xc::entity_id camera, std::shared_ptr<xc::renderer>& renderer) -> void;
#endif // GAME_SYSTEMS_H