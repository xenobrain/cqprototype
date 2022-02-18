#include "scripting.h"

#ifdef SCRIPTING_RUBY
#include <scripting/ruby/ruby_scripting.h>
#endif // SCRIPTING_RUBY

namespace xc {

auto scripting::create() -> std::shared_ptr<scripting> {
#ifdef SCRIPTING_RUBY
    return std::shared_ptr<ruby_scripting>{new ruby_scripting{}};
#endif // SCRIPTING_RUBY
    return std::shared_ptr<scripting>{new scripting{}};
}

}

