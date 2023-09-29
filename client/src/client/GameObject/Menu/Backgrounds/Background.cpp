#include "GameObject/Menu/Backgrounds/Background.hpp"
#include "Physics2D/Physics2D.hpp"
#include "PlayerEvents/Components/Clickable.hpp"
#include "PlayerEvents/PlayerManager.hpp"
#include "Renderer/AssetsManager.hpp"
#include "Scenes/Game.hpp"

void Background::init(registry &r, AssetsManager &assets)
{
    Physics2D phy;

    phy.init(r);
    assets.init(r);
}

void Background::createFst(registry &r, const Position::Data &pos,
    const Velocity::Data &vel, AssetsManager &assetsManager,
    const std::string &path)
{
    const entity &background = r.spawn_entity();

    r.add_component<Position::Component>(background, Position::Component(pos));
    r.add_component<Velocity::Component>(background, Velocity::Component(vel));
    r.add_system<Drawable::Component, Position::Component>(
        Systems::Renderer::MoveFstBackground());
    assetsManager.decor(r, background, pos, TextureSFML(path));
}

void Background::createSnd(registry &r, const Position::Data &pos,
    const Velocity::Data &vel, AssetsManager &assetsManager,
    const std::string &path)
{
    const entity &background = r.spawn_entity();

    r.add_component<Position::Component>(background, Position::Component(pos));
    r.add_component<Velocity::Component>(background, Velocity::Component(vel));
    r.add_system<Drawable::Component, Position::Component>(
        Systems::Renderer::MoveSndBackground());
    assetsManager.decor(r, background, pos, TextureSFML(path));
}