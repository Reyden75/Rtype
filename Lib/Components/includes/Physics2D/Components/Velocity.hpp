#ifndef __VELOCITY__
#define __VELOCITY__

#include <cstring>
#include <iostream>
#include <memory>

#include "IComponent.hpp"
#include "PlayerEvents/Components/Controllable.hpp"

namespace Velocity
{
    struct Data {
        float x;
        float y;
    };

    class Component : public IComponent {
      public:
        Component(const float &x, const float &y) : _velocity({x, y}){};
        Component(const Data &data) : _velocity(data){};
        Component(const char *buffer)
        {
            std::memcpy(&_velocity, buffer, sizeof(_velocity));
        };

        friend std::ostream &operator<<(std::ostream &o, const Component &c)
        {
            Data pos = c.getData();
            return o << "Velocity {" << pos.x << ", " << pos.y << "}";
        }

        std::unique_ptr<char[]> toBuffer() const override
        {
            std::unique_ptr<char[]> binary = std::make_unique<char[]>(1024);

            std::memcpy(binary.get(), &_velocity, sizeof(_velocity));
            return binary;
        };

        Data getData() const
        {
            return _velocity;
        };

        void update(const Controllable::Direction &direction)
        {
            _velocity = {0, 0};
            if (direction == Controllable::Direction::Up) {
                _velocity.y = -speed;
            }
            if (direction == Controllable::Direction::Down) {
                _velocity.y = speed;
            }
            if (direction == Controllable::Direction::Left) {
                _velocity.x = -speed;
            }
            if (direction == Controllable::Direction::Right) {
                _velocity.x = speed;
            }
        }

      private:
        Data _velocity = {0, 0};
        float speed = 250;
    };
}; // namespace Velocity

#endif /* __VELOCITY__ */