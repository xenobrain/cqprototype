#ifndef ENGINE_CORE_INPUT_H
#define ENGINE_CORE_INPUT_H

namespace xc {

enum class key { eW, eA, eS, eD, eUnknown };

class input {
public:
    auto static is_key_down(key code) -> bool;
    auto static mouse_x() -> float;
    auto static mouse_y() -> float;
};

}

#endif // ENGINE_CORE_INPUT_H