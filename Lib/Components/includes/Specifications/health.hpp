#ifndef __HEALTH__
#define __HEALTH__

#include <SFML/System.hpp>

namespace component
{
    struct health {
        health(const int &health)
            : _health(health), _maxHealth(health)
        {
        }
        void takeDamage(const int &damage)
        {
            _health -= damage;
        }

        int _health;
        int _maxHealth;
    };
} // namespace component

#endif /* __HEALTH__ */