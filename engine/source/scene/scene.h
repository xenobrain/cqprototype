#ifndef ENGINE_SCENE_SCENE_H
#define ENGINE_SCENE_SCENE_H

#include <scene/types.h>

#include <any>
#include <map>
#include <bitset>
#include <vector>
#include <typeindex>

namespace xc {

auto static component_id_pool = std::size_t{0};
using signature_type = std::bitset<sizeof(entity_id) << 3>;

class scene : public std::enable_shared_from_this<scene> {
public:
    auto static create() -> std::shared_ptr<scene>;

    ~scene();

    auto create_entity() -> entity_id {
        auto entity = _entities++;

        if (entity >= static_cast<entity_id>(_signatures.size()))
            _signatures.resize(static_cast<std::size_t>(entity + 1u));

        return entity;
    }

    auto remove_entity(entity_id entity) -> void {
        _signatures[entity].reset();
    }

    template<class T, typename... Args> auto inline add_component(entity_id entity, Args &&... args) -> T& {
        auto component_id = lookup<T>::id();

        if (component_id >= _pools.size()) _pools.resize(component_id + 1);

        if (!_pools[component_id].has_value()) _pools[component_id].template emplace<std::vector<T>>();

        auto& pool = std::any_cast<std::vector<T>&>(_pools[component_id]);

        if (entity >= pool.size()) pool.resize(_entities);

        pool[entity] = T{std::forward<Args>(args)...};
        _signatures.at(entity).set(component_id);

        return pool[entity];
    }

    template<class T> auto inline remove_component(entity_id entity) -> void {
        _signatures.at(entity).set(lookup<T>::id(), false);
    }

    template<class T> [[nodiscard]] auto inline has_component(entity_id entity) -> bool {
        return _signatures.at(entity).test(lookup<T>::id());
    }

    template<class T> [[nodiscard]] auto inline get_component(entity_id entity) -> T& {
        return std::any_cast<std::vector<T>&>(_pools[lookup<T>::id()])[entity];
    }

    struct view_t {
        std::shared_ptr<scene> world;
        std::vector<entity_id> entities;

        template<class A, class F> auto each(F&& f) -> void {
            for (auto entity : entities)
                std::invoke(std::forward<F>(f), world->template get_component<A>(entity));
        }

        template<class A, class B, class F> auto each(F&& f) -> void {
            for (auto entity : entities)
                std::invoke(std::forward<F>(f),
                            world->template get_component<A>(entity),
                            world->template get_component<A>(entity));
        }

        template<class A, class B, class C, class F> auto each(F&& f) -> void {
            for (auto entity : entities)
                std::invoke(std::forward<F>(f),
                            world->template get_component<A>(entity),
                            world->template get_component<B>(entity),
                            world->template get_component<C>(entity));
        }
    };

    template<class A> auto view() -> view_t {
        auto entities = std::vector<std::size_t>{};

        for (auto i = std::size_t{0u}; i < _signatures.size(); ++i) {
            auto signature = _signatures[i];
            auto component_id = lookup<A>::id();
            if (signature.test(component_id))
                entities.template emplace_back(i);
        }

        return view_t{shared_from_this(), std::move(entities)};
    }

    template<class A, class B> auto view() -> view_t {
        auto entities = std::vector<std::size_t>{};

        for (auto i = std::size_t{0u}; i < _signatures.size(); ++i) {
            auto signature = _signatures[i];
            if (signature.test(lookup<A>::id()) && signature.test(lookup<B>::id()))
                entities.template emplace_back(i);
        }

        return view_t{shared_from_this(), std::move(entities)};
    }

    template<class A, class B, class C> auto view() -> view_t {
        auto entities = std::vector<std::size_t>{};

        for (auto i = std::size_t{0u}; i < _signatures.size(); ++i) {
            auto signature = _signatures[i];
            if (signature.test(lookup<A>::id()) && signature.test(lookup<B>::id()) && signature.test(lookup<C>::id()))
                entities.template emplace_back(i);
        }

        return view_t{shared_from_this(), std::move(entities)};
    }

private:
    scene();

    template<class T> struct lookup {
        auto static id() -> std::size_t {
            auto static id = component_id_pool++;
            return id;
        }
    };


    entity_id _entities = 0;

    // TODO: the pools should be dense arrays-- else when we delete components a hole is left
    std::vector<std::any> _pools;
    std::vector<signature_type> _signatures;
};

}

#endif // ENGINE_SCENE_SCENE_H