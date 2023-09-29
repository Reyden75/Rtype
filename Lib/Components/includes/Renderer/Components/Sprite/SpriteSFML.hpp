#ifndef __SPRITE__
#define __SPRITE__

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>

#include "Renderer/Components/Sprite/ISprite.hpp"
#include "Renderer/Components/Texture/TextureSFML.hpp"

class SpriteSFML : public ISprite {
    using Texture = std::shared_ptr<ITexture>;
    using Position = const Position::Data &;
    using Rect = const HitBox::Data &;

  public:
    SpriteSFML(){};
    ~SpriteSFML()
    {
        std::cout << "Destroying SpriteSFML" << std::endl;
    };

    void setTexture(Texture texture)
    {
        auto textureSFML = std::dynamic_pointer_cast<TextureSFML>(texture);
        _sprite.setTexture(*textureSFML->getTexture());
    };

    void setPosition(Position position)
    {
        _sprite.setPosition({position.x, position.y});
    };

    void setHitBox(Rect hitBox)
    {
        if (hitBox.left || hitBox.top || hitBox.width || hitBox.height) {
            _sprite.setTextureRect(
                {hitBox.left, hitBox.top, hitBox.width, hitBox.height});
        }
    };

    void setScale(const float &scale = 1)
    {
        _sprite.setScale({scale, scale});
    };

    sf::Sprite getSprite() const
    {
        return _sprite;
    };

    SpriteDimensions getSpriteDimensions() const
    {
        sf::FloatRect rect = _sprite.getGlobalBounds();
        return {rect.left, rect.top, rect.width, rect.height};
    };

  private:
    sf::Sprite _sprite;
};

#endif /* __SPRITE__ */