#ifndef __CONTROLLABLE
#define __CONTROLLABLE

#include <cstring>
#include <iostream>
#include <memory>

#include "Audio/AudioSFML.hpp"
#include "IComponent.hpp"
#include "Network.hpp"
#include "PlayerEvents/Components/Input/InputSFML.hpp"

namespace Controllable
{
    enum Direction { Nothing = 0, Up = 1, Down = 2, Left = 3, Right = 4 };

    struct Data {
        Direction direction;
    };

    class Component : public IComponent {
      public:
        Component(std::function<void(const Network::request &)> send)
            : _send(send)
        {
            _audio->loadFromFile("./sprites/fire_sound.ogg");
        };
        Component(const char *buffer)
        {
            std::memcpy(&_data, buffer, sizeof(_data));
        };

        ~Component() = default;

        std::unique_ptr<char[]> toBuffer() const override
        {
            std::unique_ptr<char[]> binary = std::make_unique<char[]>(1024);

            std::memcpy(binary.get(), &_data, sizeof(_data));
            return binary;
        };

        void handleDirection()
        {
            _data.direction = Direction::Nothing;

            if (_input->isKeyZ()) {
                _data.direction = Direction::Up;
            }
            if (_input->isKeyS()) {
                _data.direction = Direction::Down;
            }
            if (_input->isKeyQ()) {
                _data.direction = Direction::Left;
            }
            if (_input->isKeyD()) {
                _data.direction = Direction::Right;
            }
            if (_input->isKeySpace())
                _audio->play();

            _send(Network::request("move", {{&_data, sizeof(_data)}}));
        }

        void execute()
        {
            _send(Network::request("shoot"));
        }

        Direction getData() const
        {
            return _data.direction;
        }

      private:
        std::shared_ptr<IInput> _input = std::make_shared<InputSFML>();
        Data _data;
        std::function<void(Network::request)> _send;
        std::shared_ptr<IAudio> _audio = std::make_shared<AudioSFML>();
    };
}; // namespace Controllable

#endif /* __CONTROLLABLE */