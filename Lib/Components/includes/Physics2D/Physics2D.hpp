#ifndef __PHYSICS_2D__
#define __PHYSICS_2D__

#include "IComponentLauncher.hpp"
#include "Physics2D/Systems/Systems.hpp"
#include "Tag/Tag.hpp"

class Physics2D : public IComponentLauncher {
  public:
    void init(registry &r) override
    {
        r.register_component<HitBox::Component>();
        r.register_component<Position::Component>();
        r.register_component<Velocity::Component>();
        r.register_component<Tag::Component>();

        r.add_system<Position::Component, Velocity::Component>(
            Systems::Physics2D::UpdatePosition());
    };

    void initServer(registry &r)
    {
        init(r);

        r.add_system<Position::Component>(Systems::Physics2D::OutOfBound());
        r.add_system<HitBox::Component, Position::Component>(Systems::Physics2D::Collide());
        // r.add_system<Position::Component>(Systems::Physics2D::OutOfBound());
    };

    void initClient(registry &r)
    {
        init(r);
    };
};

#endif /* __PHYSICS_2D__ */