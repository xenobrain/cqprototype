#include "ruby_scripting.h"

#include <mruby.h>
#include <mruby/compile.h>

namespace xc {

mrb_state* mrb = nullptr;

ruby_scripting::ruby_scripting() {
    mrb = mrb_open();
    if (!mrb) throw std::runtime_error("Could not create ruby state");

    mrb_load_string(mrb, "p 'hello world!'");
}

ruby_scripting::~ruby_scripting() {
    mrb_close(mrb);
}

}