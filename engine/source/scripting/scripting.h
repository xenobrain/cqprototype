#ifndef ENGINE_SCRIPTING_SCRIPTING_H
#define ENGINE_SCRIPTING_SCRIPTING_H

#include <scripting/types.h>

namespace xc {

class scripting {
public:
    auto static create() -> std::shared_ptr<scripting>;
};

}

#endif // ENGINE_SCRIPTING_SCRIPTING_H