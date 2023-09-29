#ifndef __REGISTRY__
#define __REGISTRY__

#include <any>
#include <functional>
#include <queue>
#include <typeindex>
#include <unordered_map>
#include "entity.hpp"
#include "sparse_array.hpp"

class registry {
  public:
    template <class Component>
    sparse_array<Component> &get_components()
    {
        return std::any_cast<sparse_array<Component> &>(
            _components_arrays.at(typeid(Component)));
    };

    template <class Component>
    sparse_array<Component> const &get_components() const
    {
        return std::any_cast<sparse_array<Component> const &>(
            _components_arrays.at(typeid(Component)));
    };

    template <class Component>
    sparse_array<Component> &register_component()
    {
        _components_arrays.try_emplace(
            typeid(Component), sparse_array<Component>{});
        _eraser_functions.push_back(
            [](registry &registry, entity const &entity) {
                registry.remove_component<Component>(entity);
            });
        return get_components<Component>();
    };

    entity spawn_entity()
    {
        if (_components_holes.size() > 0) {
            entity new_entity = entity_from_index(_components_holes.front());
            _components_holes.pop();
            return new_entity;
        }
        entity new_entity = entity_from_index(_max_id);
        _max_id++;
        return new_entity;
    };
    entity entity_from_index(std::size_t idx)
    {
        return entity(idx);
    };
    void kill_entity(const entity &e)
    {
        for (auto &eraser : _eraser_functions) {
            eraser(*this, e);
        }
        _components_holes.push(static_cast<size_t>(e));
    };

    template <typename Component>
    typename sparse_array<Component>::reference_type add_component(
        entity const &to, Component &&c)
    {
        return get_components<Component>().insert_at(
            to._size, std::forward<Component>(c));
    };

    template <typename Component, typename... Params>
    typename sparse_array<Component>::reference_type emplace_component(
        entity const &to, Params &&...p)
    {
        return get_components<Component>().emplace_at(
            to._size, std::forward<Params>(p)...);
    };

    template <typename Component>
    void remove_component(entity const &from)
    {
        if (from._size >= get_components<Component>().size()) {
            return;
        }
        return get_components<Component>().erase(from);
    };

    // template <class... Components, typename Function>
    // void add_system(Function &&f)
    // {
    //     std::function<void(registry &)> function = [f](registry &r) {
    //         f(r, r.template get_components<Components>()...);
    //     };
    //     _systems.push_back(function);
    // };

    template <class... Components, typename Function>
    void add_system(Function const &f)
    {
        std::function<void(registry &)> function = [f](registry &r) {
            f(r, r.template get_components<Components>()...);
        };
        _systems.push_back(function);
    };

    void run_systems()
    {
        for (const auto &system : _systems) {
            try {
                system(*this);
            } catch (const std::bad_optional_access &e) {
                std::cout << "Error : running systems : " << e.what() << std::endl;
            }
        }
    };

  private:
    using system_function = std::function<void(registry &)>;
    using eraser_function = std::function<void(registry &, entity const &)>;

    size_t _max_id = 0;
    std::queue<size_t> _components_holes;
    std::vector<system_function> _systems;
    std::vector<eraser_function> _eraser_functions;
    std::unordered_map<std::type_index, std::any> _components_arrays;
};

#endif /* __REGISTRY__ */