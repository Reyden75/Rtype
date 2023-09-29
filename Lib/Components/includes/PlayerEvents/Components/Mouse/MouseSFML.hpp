#ifndef __MOUSE__
#define __MOUSE__

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Physics2D/Components/Position.hpp"
#include "PlayerEvents/Components/Mouse/IMouse.hpp"

class MouseSFML : public IMouse {
  public:
    MouseSFML() = default;
    ~MouseSFML() = default;

    bool isLeftButtonMousePressed() const
    {
        return sf::Mouse::isButtonPressed(sf::Mouse::Left);
    };

    Position::Data getMousePosition() const
    {
        sf::Vector2i mousePosition = sf::Mouse::getPosition();
        Position::Data position = {static_cast<float>(mousePosition.x),
            static_cast<float>(mousePosition.y)};
        return position;
    };
};

#endif /* __MOUSE__ */