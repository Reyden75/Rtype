#ifndef __GAME__
#define __GAME__

#include "IScene.hpp"
#include "Network.hpp"
#include "Renderer/AssetsManager.hpp"
#include "UDP.hpp"
#include "registry.hpp"

class Game : public IScene {
  using Request = const Network::request &;
  using Response = const Network::response &;

  public:
    Game(const std::string &, const int &, int);
    ~Game() = default;

    void load();

    void confirmJoin(Request, Response);
    void updatePosition(Request, Response);
    void playerJoin(Request, Response);
    void enemyJoin(Request, Response);
    void bulletJoin(Request, Response);
    void killEnemy(Request req, Response res);
    void manageStartGame();

  private:
    registry _registry;
    AssetsManager _assetsManager;
    UDP::Service _udpService;
    UDP::Endpoint _serverEndpoint;
};

#endif