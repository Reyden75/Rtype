#ifndef __ASSETS_MANAGER__
#define __ASSETS_MANAGER__

#include <map>
#include <memory>

#include "IComponentLauncher.hpp"

#include "Renderer/Components/Drawable.hpp"
#include "Renderer/Systems/Systems.hpp"

#include "Renderer/Components/Sprite/ISprite.hpp"
#include "Renderer/Components/Sprite/SpriteSFML.hpp"

#include "Renderer/Components/Texture/ITexture.hpp"
#include "Renderer/Components/Texture/TextureSFML.hpp"

inline const std::string tPlayer = "./sprites/r-typesheet42.gif";
inline const std::string tBullet = "./sprites/r-typesheet1.gif";

class AssetsManager : public IComponentLauncher {
  public:
    AssetsManager() = default;
    ~AssetsManager()
    {
        std::cout << "Destroying AssetsManager" << std::endl;
    };

    void init(registry &r) override
    {
        r.register_component<Drawable::Component>();

        r.add_system<Drawable::Component, Position::Component>(
            Systems::Renderer::Draw());
        r.add_system<Drawable::Component, Position::Component>(
            Systems::Renderer::MoveFstBackground());
        r.add_system<Drawable::Component, Position::Component>(
            Systems::Renderer::MoveSndBackground());
    };

    void player(registry &r, const entity &e, const Position::Data &pos,
        const HitBox::Data &hb)
    {
        std::shared_ptr<ITexture> texture;

        if (_player) {
            texture = _player;
        } else {
            texture = std::make_shared<TextureSFML>(tPlayer);
            if (!texture->loadFromFile()) {
                std::cout << "Can't load " << tPlayer << " from file !"
                          << std::endl;
                return;
            }
            _player = texture;
        }
        r.add_component<Drawable::Component>(
            e, Drawable::Component(pos, hb, texture, 4));
    };

    void enemy(registry &r, const entity &e, const Position::Data &pos,
        const HitBox::Data &hb, const std::string &path)
    {
        std::shared_ptr<ITexture> texture;

        if (_enemy) {
            texture = _enemy;
        } else {
            texture = std::make_shared<TextureSFML>(path);
            if (!texture->loadFromFile()) {
                std::cout << "Can't load " << path << " from file !"
                          << std::endl;
                return;
            }
            _enemy = texture;
        }
        r.add_component<Drawable::Component>(
            e, Drawable::Component(pos, hb, texture, 4));
    };

    void bullet(registry &r, const entity &e, const Position::Data &pos,
        const HitBox::Data &hb)
    {
        std::shared_ptr<ITexture> texture;

        if (_bullet) {
            texture = _bullet;
        } else {
            texture = std::make_shared<TextureSFML>(tBullet);
            if (!texture->loadFromFile()) {
                std::cout << "Can't load " << tBullet << " from file !"
                          << std::endl;
                return;
            }
            _bullet = texture;
        }
        r.add_component<Drawable::Component>(
            e, Drawable::Component(pos, hb, texture, 1));
    };

    void button(registry &r, const entity &e, const Position::Data &pos,
        const TextureSFML &t)
    {
        std::shared_ptr<ITexture> texture;

        texture = std::make_shared<TextureSFML>(t);
        if (!texture->loadFromFile()) {
            std::cout << "Can't load " << &t << " from file !" << std::endl;
            return;
        }
        _button = texture;
        r.add_component<Drawable::Component>(
            e, Drawable::Component(pos, {}, texture));
    };

    void decor(registry &r, const entity &e, const Position::Data &pos,
        const TextureSFML &t)
    {
        std::shared_ptr<ITexture> texture;

        texture = std::make_shared<TextureSFML>(t);
        if (!texture->loadFromFile()) {
            std::cout << "Can't load " << &t << " from file !" << std::endl;
            return;
        }
        _decor = texture;
        r.add_component<Drawable::Component>(
            e, Drawable::Component(pos, {}, texture));
    };

  private:
    std::shared_ptr<ITexture> _player;
    std::shared_ptr<ITexture> _bullet;
    std::shared_ptr<ITexture> _button;
    std::shared_ptr<ITexture> _decor;
    std::shared_ptr<ITexture> _enemy;
};

#endif /* __ASSETS_MANAGER__ */