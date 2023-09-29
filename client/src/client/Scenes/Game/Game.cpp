#include "Scenes/Game.hpp"
#include "Physics2D/Physics2D.hpp"
#include "PlayerEvents/PlayerManager.hpp"
#include "Renderer/AssetsManager.hpp"
#ifdef __unix__
    #include <unistd.h>
#elif defined _WIN32
    #include <windows.h>
    #define sleep(x) Sleep(1000 * (x))
#endif

Game::Game(const std::string &ip, const int &port, int roomId)
    : _udpService(Router({
        Route("confirm-join",
            [this](Request req, Response res) {
                confirmJoin(req, res);
            }),
        Route("player-join",
            [this](Request req, Response res) {
                playerJoin(req, res);
            }),
        Route("enemy-join",
            [this](Request req, Response res) {
                enemyJoin(req, res);
            }),
        Route("bullet-join",
            [this](Request req, Response res) {
                bulletJoin(req, res);
            }),
        Route("update-player-position",
            [this](Request req, Response res) {
                updatePosition(req, res);
            }),
        Route("kill-enemy",
            [this](Request req, Response res) {
                killEnemy(req, res);
            }),
    }))
{
    Physics2D physics2D;
    PlayerManager playerManager;

    physics2D.initClient(_registry);
    _assetsManager.init(_registry);
    playerManager.init(_registry);

    _udpService.listenAsync();
    _serverEndpoint = UDP::Endpoint(UDP::Address::from_string(ip), port);
    _udpService.send(
        _serverEndpoint, Network::request("join", {{&roomId, sizeof(int)}}));
}

void Game::killEnemy(Request req, Response res)
{
    std::cout << "Entity id = " << req.entityId << std::endl;
    const entity &e = _registry.entity_from_index(req.entityId);
    _registry.kill_entity(e);
};

void Game::manageStartGame()
{
    static bool started = false;

    if (WindowManager::window->isEventKeyReleased()
        && WindowManager::window->isKeyEnterCode() && !started) {
        std::cout << "Asked to start the game" << std::endl;
        started = true;
        _udpService.send(_serverEndpoint, Network::request("start-game"));
    }
}

void Game::confirmJoin(Request req, Response res)
{
    std::cout << "Entity id = " << req.entityId << std::endl;
    const entity &e = _registry.entity_from_index(req.entityId);
    size_t idx = 0;

    Position::Component pos(&req.body[idx]);
    idx += sizeof(Position::Data);
    Velocity::Component vel(&req.body[idx]);
    idx += sizeof(Velocity::Data);
    HitBox::Component hb(&req.body[idx]);

    _registry.add_component<Position::Component>(e, std::move(pos));
    _registry.add_component<Velocity::Component>(e, std::move(vel));
    _registry.add_component<HitBox::Component>(e, std::move(hb));

    _registry.add_component<Controllable::Component>(
        e, Controllable::Component([this, e](Request req) {
            Network::request newReq = req;
            newReq.entityId = e;
            _udpService.send(_serverEndpoint, newReq);
        }));

    _assetsManager.player(_registry, e, pos.getData(), hb.getData());

    std::cout << "[LOG] Spawn   | " << pos << " " << vel << " " << hb
              << std::endl;
}

void Game::playerJoin(Request req, Response res)
{
    std::cout << "Entity id = " << req.entityId << std::endl;
    const entity &e = _registry.entity_from_index(req.entityId);
    size_t idx = 0;

    Position::Component pos(&req.body[idx]);
    idx += sizeof(Position::Data);
    Velocity::Component vel(&req.body[idx]);
    idx += sizeof(Velocity::Data);
    HitBox::Component hb(&req.body[idx], [](const std::size_t &e) {

    });

    _registry.add_component<Position::Component>(e, std::move(pos));
    _registry.add_component<Velocity::Component>(e, std::move(vel));
    _registry.add_component<HitBox::Component>(e, std::move(hb));

    _assetsManager.player(_registry, e, pos.getData(), hb.getData());

    std::cout << "[LOG] Player Spawn   | " << pos << " " << vel << " " << hb
              << std::endl;
}

void Game::enemyJoin(Request req, Response res)
{
    const entity &e = _registry.entity_from_index(req.entityId);
    size_t idx = 0;
    char path[260];

    try {
        Velocity::Component vel(&req.body[idx]);
        idx += sizeof(Velocity::Data);
        Position::Component pos(&req.body[idx]);
        idx += sizeof(Position::Data);
        HitBox::Component hb(&req.body[idx], [e](const std::size_t &entity) {
            std::cout << e << " collided" << std::endl;
        });
        idx += sizeof(HitBox::Data);
        memcpy(path, &req.body[idx], 260);

        _registry.add_component<Position::Component>(
            e, Position::Component(pos));
        _registry.add_component<Velocity::Component>(
            e, Velocity::Component(vel));
        _registry.add_component<HitBox::Component>(e, HitBox::Component(hb));

        _assetsManager.enemy(
            _registry, e, pos.getData(), hb.getData(), std::string(path));

        std::cout << "[LOG] Enemy Spawn   | " << pos << " " << vel << " " << hb
                  << std::endl;
    } catch (const std::exception &e) {
        std::cout << "Error : Enemy join :" << e.what() << std::endl;
    }
}

void Game::updatePosition(Request req, Response res)
{
    const entity &e = _registry.entity_from_index(req.entityId);

    Position::Component pos(req.body);

    try {
        auto &position = _registry.get_components<Position::Component>()[e];
        if (position.has_value()) {
            position.value().update(pos.getData());
        }
    } catch (const std::bad_optional_access &e) {
        std::cout << "Update position error: " << e.what() << std::endl;
        return;
    }
}

void Game::bulletJoin(Request req, Response res)
{
    const entity &e = _registry.entity_from_index(req.entityId);
    size_t idx = 0;

    Position::Component pos(&req.body[idx]);
    idx += sizeof(Position::Data);
    Velocity::Component vel(&req.body[idx]);
    idx += sizeof(Velocity::Data);
    HitBox::Component hb(&req.body[idx], [e](const std::size_t &entity) {
        std::cout << e << " collided" << std::endl;
    });

    _registry.add_component<Position::Component>(e, std::move(pos));
    _registry.add_component<Velocity::Component>(e, std::move(vel));
    _registry.add_component<HitBox::Component>(e, std::move(hb));

    _assetsManager.bullet(_registry, e, pos.getData(), hb.getData());

    std::cout << "[LOG] Shoot" << pos << std::endl;
}

void Game::load()
{
    manageStartGame();
    _registry.run_systems();
}