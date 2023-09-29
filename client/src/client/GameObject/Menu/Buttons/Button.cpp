#include "GameObject/Menu/Buttons/Button.hpp"
#include "Physics2D/Physics2D.hpp"
#include "Physics2D/Components/Position.hpp"
#include "PlayerEvents/Components/Clickable.hpp"
#include "PlayerEvents/PlayerManager.hpp"
#include "Renderer/AssetsManager.hpp"
#include "Scenes/Game.hpp"

Button::Button()
{
}

void Button::init(registry &r, AssetsManager &assets)
{
    Physics2D phy;

    phy.init(r);
    assets.init(r);

    r.register_component<Clickable::Component>();
}

void Button::create(registry &r, std::stack<std::unique_ptr<IScene>> &scenes,
    const std::string &ip, const int &port, const Position::Data &pos,
    const HitBox::Data &hb, const std::function<void()> &onClick,
    AssetsManager &assetsManager, const std::string &path)
{
    const entity &button = r.spawn_entity();

    r.add_component<Position::Component>(button, Position::Component(pos));
    r.add_component<HitBox::Component>(button, HitBox::Component(hb));
    r.add_component<Clickable::Component>(
        button, Clickable::Component(onClick));
    r.add_system<Clickable::Component, HitBox::Component>(
        Systems::PlayerEvents::ButtonClick());
    assetsManager.button(r, button, pos, TextureSFML(path));
}