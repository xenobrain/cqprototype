#include <engine.h>

class game {
public:
    game();
    ~game();

    auto run() -> void;
    auto tick() -> void;

private:
    auto initialize() -> void;

    // Entities
    xc::entity_id _player, _camera;

    // Systems
    std::shared_ptr<xc::scripting> _scripting;
    std::shared_ptr<xc::platform> _platform;
    std::shared_ptr<xc::renderer> _renderer;
    std::shared_ptr<xc::physics> _physics;
    std::shared_ptr<xc::scene> _scene;
    std::shared_ptr<xc::audio> _audio;
    xc::timer _timer;

    // State
    bool _initialized = false, _running = true;
};
