#ifndef __DAMAGE__
#define __DAMAGE__

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace component
{
    struct damage {
        damage(int damage): _damage(damage) {};

        int _damage;
    };
} // namespace component

#endif /* __DAMAGE__ */