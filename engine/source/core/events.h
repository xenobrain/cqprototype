#ifndef ENGINE_CORE_EVENTS_H
#define ENGINE_CORE_EVENTS_H

#include <any>
#include <map>
#include <typeindex>
#include <functional>

#include <core/types.h>

struct event {
    virtual ~event() = default;
};

struct quit_event {};

namespace xc {

class event_system {
public:
    auto static get() -> event_system& {
        auto static instance = event_system{};
        return instance;
    }

    template<class T, class... Args> auto on(std::function<void(T const&)>&& func) {
        _event_map.emplace(std::type_index{typeid(T)}, std::forward<std::function<void(T const&)>>(func));
    }

    template<class T, class... Args> auto publish(Args&&... args) {
        auto const map_range = _event_map.equal_range(std::type_index{typeid(T)});
        for (auto item = map_range.first; item != map_range.second; ++item)
            std::any_cast<std::function<void(T const&)>>(item->second)(T{std::forward<Args>(args)...});
    }

private:
    std::multimap<std::type_index const, std::any> _event_map;
};

}

#endif // ENGINE_CORE_EVENTS_H