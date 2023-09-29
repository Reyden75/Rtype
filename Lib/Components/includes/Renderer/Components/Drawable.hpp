#ifndef __DRAWABLE__
#define __DRAWABLE__

#include "Renderer/Components/Sprite/SpriteSFML.hpp"
#include "Renderer/Components/Texture/TextureSFML.hpp"
#include "Renderer/WindowManager.hpp"

#include <cstring>
#include <iostream>
#include <memory>

namespace Drawable
{
    struct Data {
        std::shared_ptr<ISprite> sprite;
        std::shared_ptr<ITexture> texture;
    };

    class Component : public IComponent {
      public:
        Component(const Position::Data &pos, const HitBox::Data &hb,
            std::shared_ptr<ITexture> texture, int scl = 1)
            : _windowManager(1920, 1080)
        {
            _drawable.sprite = std::make_shared<SpriteSFML>();
            _drawable.texture = texture;

            _drawable.sprite->setTexture(texture);
            _drawable.sprite->setPosition(pos);
            _drawable.sprite->setHitBox(hb);
            _drawable.sprite->setScale(scl);
        };

        std::unique_ptr<char[]> toBuffer() const
        {
            std::unique_ptr<char[]> binary = std::make_unique<char[]>(1024);

            std::memcpy(binary.get(), &_drawable, sizeof(_drawable));
            return binary;
        };

        void updatePosition(const Position::Data &pos)
        {
            _drawable.sprite->setPosition(pos);
        };

        void draw() const
        {
            _windowManager.window->draw(_drawable.sprite);
        };

        SpriteDimensions getSpriteDimensions() const
        {
            return _drawable.sprite->getSpriteDimensions();
        };

      private:
        Data _drawable;
        WindowManager _windowManager;
    };
}; // namespace Drawable

#endif /* __DRAWABLE__ */