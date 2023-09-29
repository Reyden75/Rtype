#ifndef __CLICKABLE__
#define __CLICKABLE__

#include <cstring>
#include <iostream>
#include <memory>

#include "IComponent.hpp"
#include "PlayerEvents/Components/Mouse/MouseSFML.hpp"

#include "Renderer/WindowManager.hpp"

namespace Clickable
{
    class Component : public IComponent {
      public:
        Component(const std::function<void()> &onClick) : _onClick(onClick){};
        ~Component() = default;

        std::unique_ptr<char[]> toBuffer() const override
        {
            std::unique_ptr<char[]> binary = std::make_unique<char[]>(1024);

            return binary;
        };

        bool isClick(const HitBox::Data &hb) const
        {
            return _input->getMousePosition().x >= hb.left
                && _input->getMousePosition().x <= hb.left + hb.width
                && _input->getMousePosition().y >= hb.top
                && _input->getMousePosition().y <= hb.top + hb.height;
        }

        void execute() const
        {
            _onClick();
        }

      private:
        std::function<void()> _onClick;
        std::shared_ptr<IMouse> _input = std::make_shared<MouseSFML>();
    };
}; // namespace Clickable

#endif /* __CLICKABLE__ */