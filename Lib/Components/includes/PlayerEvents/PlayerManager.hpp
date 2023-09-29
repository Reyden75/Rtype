#ifndef __PLAYER_MANAGER__
#define __PLAYER_MANAGER__

#include "IComponentLauncher.hpp"
#include "Physics2D/Components/Velocity.hpp"
#include "PlayerEvents/Components/Controllable.hpp"
#include "PlayerEvents/Systems/Systems.hpp"

class PlayerManager : public IComponentLauncher {
  public:
    PlayerManager() = default;
    ~PlayerManager()
    {
        std::cout << "Destroying PlayerManager" << std::endl;
    };

    void init(registry &registry) override
    {
        registry.register_component<Controllable::Component>();

        registry.add_system<Controllable::Component, Velocity::Component>(
            Systems::PlayerEvents::Control());
        registry.add_system<Controllable::Component>(
            Systems::PlayerEvents::Shoot());
    }
};

#endif /* __PLAYER_MANAGER__ */