#ifndef ENGINE_PLATFORM_PLATFORM_H
#define ENGINE_PLATFORM_PLATFORM_H

#include <platform/types.h>

namespace xc {

class platform {
public:
    auto static create() -> std::shared_ptr<platform>;

    virtual auto create_window(int width, int height) -> void = 0;

    virtual auto tick() -> void = 0;
};

}

#endif // ENGINE_PLATFORM_PLATFORM_H