#include "Room.hpp"
#include "Tag/Tag.hpp"
#include <ostream>
#include <chrono>

Room::Room(UDP::Service &service) : _udpService(service)
{
    Physics2D physics2D;
    _parser = std::make_shared<TinyXMLParser>("levels/lvl1.xml");
    _parser->init();
    _clock = std::chrono::high_resolution_clock::now();
    _time = 0;
    physics2D.initServer(_registry);
}

Room::~Room()
{
}

void Room::sendToAll(Request req)
{
    for (const auto &client : _clients) {
        _udpService.send(client.second, req);
    }
}

void Room::sendToAllOthers(const Room::Endpoint &exclude, Request req)
{
    for (const auto &client : _clients) {
        if (client.second != exclude) {
            _udpService.send(client.second, req);
        }
    }
}

std::map<std::size_t, Room::Endpoint> Room::getClients() const
{
    return _clients;
}

void Room::updateSystems()
{
    if (_isGameStarted == true) {
        auto now = std::chrono::high_resolution_clock::now();
        auto duration_ms =
            std::chrono::duration_cast<std::chrono::seconds>(now - _clock);
        if (duration_ms.count() >= 1) {
            _clock = std::chrono::high_resolution_clock::now();
            _time++;
            std::cout << "Time : " << _time << std::endl;
            spawnEnemy();
        }
        _registry.run_systems();
    };
}

void Room::addClient(Response response)
{
    if (_isGameStarted) {
        return;
    }
    std::cout << response.endpoint << " try to join" << std::endl;
    const entity &e = _registry.spawn_entity();

    _clients.emplace(e, response.endpoint);

    Position::Data pos = {50, 150.0f * e};
    Velocity::Data vel = {0, 0};
    HitBox::Data hb = {0, 0, 33, 17};

    const std::map<void *, const std::size_t> contents = {
        {&pos, sizeof(pos)}, {&vel, sizeof(vel)}, {&hb, sizeof(hb)}};

    _registry.add_component<Position::Component>(e, Position::Component(pos));
    _registry.add_component<Velocity::Component>(e, Velocity::Component(vel));
    _registry.add_component<HitBox::Component>(e, HitBox::Component(hb));
    _registry.add_component<Tag::Component>(e, Tag::Component("player"));


    std::cout << response.endpoint << " joined" << std::endl;
    response.send(Network::request("confirm-join", contents, e));
    sendToAllOthers(
        response.endpoint, Network::request("player-join", contents, e));
    for (auto &client : _clients) {
        if (client.first != e) {
            auto playerPosition =
                _registry.get_components<Position::Component>()[client.first];
            auto playerVelocity =
                _registry.get_components<Velocity::Component>()[client.first];
            auto playerHitBox =
                _registry.get_components<HitBox::Component>()[client.first];

            if (playerPosition.has_value() && playerVelocity.has_value()
                && playerHitBox.has_value()) {
                Position::Data position = playerPosition.value().getData();
                Velocity::Data velocity = playerVelocity.value().getData();
                HitBox::Data hitBox = playerHitBox.value().getData();

                const std::map<void *, const std::size_t>
                    playerPositionContent = {{&position, sizeof(position)},
                        {&velocity, sizeof(velocity)},
                        {&hitBox, sizeof(hitBox)}};

                response.send(Network::request(
                    "player-join", playerPositionContent, client.first));
            }
        }
    }
}

void Room::updatePlayerPositions(
    const Controllable::Direction &direction, const size_t &e)
{
    try {
        auto &playerVelocity =
            _registry.get_components<Velocity::Component>()[e];
        auto &playerPosition =
            _registry.get_components<Position::Component>()[e];

        Position::Data pos;

        if (playerVelocity.has_value() && playerPosition.has_value()) {
            pos = playerPosition.value().getData();
            playerVelocity.value().update(direction);

            const std::map<void *, const std::size_t> contents = {
                {&pos, sizeof(pos)}};

            sendToAll(
                 Network::request("update-player-position", contents, e));
        }
    } catch (const std::bad_optional_access &e) {
        std::cout << "Update plater position error: " << e.what() << std::endl;
        return;
    }
}

void Room::spawnEnemy()
{
    for (const Game::enemy &enemy : _parser->getEnemies()) {
        if (_time >= enemy._appearanceTime
            && _time <= enemy._appearanceTime + enemy._duration
            && _time % enemy._spawnInterval == 0) {
            try {
                int randNum = rand() % 2000;
                std::cout << "Enemy spawned : " << enemy._name << std::endl;
                auto e = _registry.spawn_entity();
                Velocity::Data velocity = {-enemy._velocity, 0};
                Position::Data position = {2000, static_cast<float>(randNum)};
                HitBox::Data hitBox = enemy.rect;
                char path[260];
                strcpy(path, enemy._sprite.c_str());
                _registry.add_component<Velocity::Component>(
                    e, Velocity::Component(velocity));
                _registry.add_component<Position::Component>(
                    e, Position::Component(position));
                _registry.add_component<HitBox::Component>(
                    e, HitBox::Component(hitBox));
                const std::map<void *, const std::size_t> contents = {
                    {&velocity, sizeof(velocity)},
                    {&position, sizeof(position)}, {&hitBox, sizeof(hitBox)},
                    {&path, sizeof(path)}

                };
                sendToAll(Network::request("enemy-join", contents, e));
            } catch (const std::exception &e) {
                std::cout << "Error : Spawning enemy : " << e.what() << std::endl;
            }
        }
    }
}

void Room::destroyEnemy()
{

}

void Room::playerShoot(const size_t &e)
{
    const entity &bullet = _registry.spawn_entity();
    Position::Data pos;
    Velocity::Data vel = {700, 0};
    HitBox::Data hb = {125, 150, 75, 20};

    try {
        auto &playerPos = _registry.get_components<Position::Component>()[e];
        if (playerPos.has_value()) {
            pos = playerPos.value().getData();

            pos.x += 50;
            pos.y += 50;

            _registry.add_component<Position::Component>(
                bullet, Position::Component(pos));
            _registry.add_component<Velocity::Component>(
                bullet, Velocity::Component(vel));
            _registry.add_component<HitBox::Component>(bullet,
                HitBox::Component(
                    hb, [this, bullet](const std::size_t &entity) {
                        std::cout << "Bullet hit smth" << std::endl;
                        auto e = _registry.entity_from_index(entity);
                        _registry.kill_entity(e);
                        sendToAll(Network::request("kill-enemy", {}, e));
                        _registry.kill_entity(bullet);
                        sendToAll(Network::request("kill-enemy", {}, bullet));
                    }));
            const std::map<void *, const std::size_t> contents = {
                {&pos, sizeof(pos)}, {&vel, sizeof(vel)}, {&hb, sizeof(hb)}};

            sendToAll(Network::request("bullet-join", contents, bullet));
        }
    } catch (const std::bad_optional_access &e) {
        std::cout << "Player Shoot Error: " << e.what() << std::endl;
        return;
    }
}

void Room::startGame()
{
    std::cout << "Game started" << std::endl;
    _isGameStarted = true;
}