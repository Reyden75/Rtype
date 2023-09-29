#ifndef __INPUT__
#define __INPUT__

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Physics2D/Components/Position.hpp"
#include "PlayerEvents/Components/Input/IInput.hpp"

class InputSFML : public IInput {
  public:
    InputSFML() = default;
    ~InputSFML() = default;

    bool isKeyPressed(const int &key) const
    {
        return sf::Keyboard::isKeyPressed(sf::Keyboard::Key(key));
    }

    bool isKeyZ() const
    {
        return isKeyPressed(sf::Keyboard::Z);
    };

    bool isKeyQ() const
    {
        return isKeyPressed(sf::Keyboard::Q);
    };

    bool isKeyS() const
    {
        return isKeyPressed(sf::Keyboard::S);
    };

    bool isKeyD() const
    {
        return isKeyPressed(sf::Keyboard::D);
    };

    bool isKeySpace() const
    {
        return isKeyPressed(sf::Keyboard::Space);
    };

    bool isKeyEnter() const
    {
        return isKeyPressed(sf::Keyboard::Enter);
    };
};

#endif /* __INPUT__ */