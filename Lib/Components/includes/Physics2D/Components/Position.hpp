#ifndef __POSITION__
#define __POSITION__

#include <cstring>
#include <iostream>
#include <memory>
#include <chrono>

#include "IComponent.hpp"
#include "Physics2D/Components/Velocity.hpp"

namespace Position
{
    struct Data {
        float x;
        float y;
    };

    class Component : public IComponent {
      public:
        Component(const float &x, const float &y) : _position({x, y}){};
        Component(const Data &data) : _position(data){};
        Component(const char *buffer)
        {
            std::memcpy(&_position, buffer, sizeof(_position));
        };

        ~Component() = default;

        friend std::ostream &operator<<(std::ostream &o, const Component &c)
        {
            Data pos = c.getData();
            return o << "Position {" << pos.x << ", " << pos.y << "}";
        }

        std::unique_ptr<char[]> toBuffer() const override
        {
            std::unique_ptr<char[]> binary = std::make_unique<char[]>(1024);
            std::memcpy(binary.get(), &_position, sizeof(_position));
            return binary;
        };

        void update(const Velocity::Data &vel,
            const std::chrono::time_point<std::chrono::high_resolution_clock> &updateTime)
        {
            _position.x += vel.x;
            _position.y += vel.y;
            _lastUpdate = updateTime;
        }

        void update(const Position::Data &pos)
        {
            _position.x = pos.x;
            _position.y = pos.y;
        }

        bool isOutOfBound() const
        {
            return (_position.x > 3000 || _position.x < -3000
                || _position.y > 3000 || _position.y < -3000);
        }

        Data getData() const
        {
            return _position;
        };

        std::chrono::time_point<std::chrono::high_resolution_clock> getLastUpdate() const
        {
            return _lastUpdate;
        }

      private:
        Data _position;
        std::chrono::time_point<std::chrono::high_resolution_clock>
            _lastUpdate = std::chrono::high_resolution_clock::now();
    };
}; // namespace Position

#endif /* __POSITION__ */