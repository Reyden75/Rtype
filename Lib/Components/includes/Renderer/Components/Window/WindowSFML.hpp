#ifndef __WINDOW__
#define __WINDOW__

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <memory>
#include <vector>

#include "Renderer/Components/Sprite/SpriteSFML.hpp"
#include "Renderer/Components/Window/IWindow.hpp"

class WindowSFML : public IWindow {
  public:
    WindowSFML(const int &width, const int &height)
        : _window(sf::VideoMode(width, height), "R-Type"){};
    ~WindowSFML()
    {
        std::cout << "WindowSFML destroyed" << std::endl;
    };

    bool isOpen() const override
    {
        return _window.isOpen();
    };

    void clear() override
    {
        _window.clear();
    };

    void updateEvents() override
    {
        sf::Event event;

        _events.clear();
        while (_window.pollEvent(event)) {
            _events.push_back(event);
        }
    }

    bool checkEventType(const sf::Event::EventType &eventType) const
    {
        for (const sf::Event &e : _events) {
            if (e.type == eventType) {
                return true;
            }
        }
        return false;
    }

    bool checkKeyCode(const sf::Keyboard::Key &key) const
    {
        for (const sf::Event &e : _events) {
            if (e.key.code == key) {
                return true;
            }
        }
        return false;
    }

    bool isEventClose() const override
    {
        return checkEventType(sf::Event::Closed);
    };

    bool isEventButtonPressed() const override
    {
        return checkEventType(sf::Event::MouseButtonPressed);
    };

    bool isEventKeyReleased() const override
    {
        return checkEventType(sf::Event::KeyReleased);
    };

    bool isKeySpaceCode() const override
    {
        return checkKeyCode(sf::Keyboard::Space);
    }

    bool isKeyEnterCode() const override
    {
        return checkKeyCode(sf::Keyboard::Enter);
    }

    void display() override
    {
        _window.display();
    };

    void close() override
    {
        _window.close();
    }

    void draw(std::shared_ptr<ISprite> sprite) override
    {
        auto spriteSFML = std::dynamic_pointer_cast<SpriteSFML>(sprite);
        _window.draw(spriteSFML->getSprite());
    };

  private:
    std::vector<sf::Event> _events;
    sf::RenderWindow _window;
};

#endif /* __WINDOW__ */
