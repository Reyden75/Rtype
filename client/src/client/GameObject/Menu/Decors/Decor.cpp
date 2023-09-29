#include "GameObject/Menu/Decors/Decor.hpp"
#include "Physics2D/Physics2D.hpp"
#include "PlayerEvents/Components/Clickable.hpp"
#include "PlayerEvents/PlayerManager.hpp"
#include "Renderer/AssetsManager.hpp"
#include "Scenes/Game.hpp"

Decor::Decor()
{
}

void Decor::init(registry &r, AssetsManager &assets)
{
    assets.init(r);
}

void Decor::create(registry &r, const Position::Data &pos,
    AssetsManager &assetsManager, const std::string &path)
{
    const entity &decor = r.spawn_entity();

    r.add_component<Position::Component>(decor, Position::Component(pos));
    assetsManager.decor(r, decor, pos, TextureSFML(path));
}

void Decor::createMoving(registry &r, const Position::Data &pos,
    const Velocity::Data &vel, AssetsManager &assetsManager,
    const std::string &path)
{
    const entity &decor = r.spawn_entity();

    r.add_component<Position::Component>(decor, Position::Component(pos));
    r.add_component<Velocity::Component>(decor, Velocity::Component(vel));
    r.add_system<Drawable::Component, Position::Component>(
        Systems::Renderer::Draw());
    assetsManager.decor(r, decor, pos, TextureSFML(path));
}