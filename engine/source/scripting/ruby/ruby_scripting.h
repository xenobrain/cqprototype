#ifndef ENGINE_SCRIPTING_RUBY_RUBY_SCRIPTING_H
#define ENGINE_SCRIPTING_RUBY_RUBY_SCRIPTING_H

#include <scripting/scripting.h>

namespace xc {

class ruby_scripting : public scripting {
    friend class scripting;

public:
    ~ruby_scripting();

private:
    ruby_scripting();
};

}

#endif // ENGINE_SCRIPTING_RUBY_RUBY_SCRIPTING_H