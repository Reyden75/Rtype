#ifndef __HIT_BOX__
#define __HIT_BOX__

#include "IComponent.hpp"

#include <cstring>
#include <iostream>
#include <memory>
#include <entity.hpp>
#include <functional>

namespace HitBox
{
    struct Data {
        int left;
        int top;
        int width;
        int height;
    };

    class Component : public IComponent {
      public:
        Component(
            const int &left, const int &top, const int &width,
            const int &height,
            std::function<void(const std::size_t &)> onCollide =
                [](const std::size_t &entity) {
                })
            : _hitBox({left, top, width, height}), _onCollide(onCollide){};
        Component(
            const Data &data,
            std::function<void(const std::size_t &)> onCollide =
                [](const std::size_t &entity) {
                })
            : _hitBox(data), _onCollide(onCollide){};
        Component(
            const char *buffer,
            std::function<void(const std::size_t &)> onCollide =
                [](const std::size_t &entity) {
                })
            : _onCollide(onCollide)
        {
            std::memcpy(&_hitBox, buffer, sizeof(_hitBox));
        };

        friend std::ostream &operator<<(std::ostream &o, const Component &c)
        {
            Data hb = c.getData();
            return o << "HitBox {" << hb.left << ", " << hb.top << ", "
                     << hb.width << ", " << hb.height << "}";
        }

        std::unique_ptr<char[]> toBuffer() const override
        {
            std::unique_ptr<char[]> binary = std::make_unique<char[]>(1024);

            std::memcpy(binary.get(), &_hitBox, sizeof(_hitBox));
            return binary;
        };

        Data getData() const
        {
            return _hitBox;
        };

        bool isColliding(const Data &other) const
        {
            return (_hitBox.left < other.left + other.width
                && _hitBox.left + _hitBox.width > other.left
                && _hitBox.top < other.top + other.height
                && _hitBox.top + _hitBox.height > other.top);
        };

        void execute(const size_t &entity) const
        {
            _onCollide(entity);
        };

        void update(const int &x, const int &y)
        {
            _hitBox.left = x;
            _hitBox.top = y;
        }

      private:
        Data _hitBox;
        std::function<void(const std::size_t &)> _onCollide;
    };
}; // namespace HitBox

#endif /* __HIT_BOX__ */