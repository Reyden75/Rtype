#include "Scenes/Create.hpp"
#include "GameObject/Menu/Backgrounds/Background.hpp"
#include "GameObject/Menu/Buttons/Button.hpp"
#include "GameObject/Menu/Decors/Decor.hpp"
#include "Scenes/Game.hpp"
#include "Scenes/Join.hpp"

Create::Create(std::stack<std::unique_ptr<IScene>> &scenes,
    const std::string &ip, const int &port, const AssetsManager &assetsManager)
    : _scenes(scenes), _assetsManager(assetsManager),
      _udpService(Router({Route("confirm-create-room",
          [this, ip, port](
              const Network::request &req, const Network::response &res) {
              int roomId;
              std::memcpy(&roomId, req.body, sizeof(int));
              _scenes.push(std::make_unique<Game>(ip, port, roomId));
          })}))
{
    _udpService.listenAsync();
    _udpService.send(UDP::Endpoint(UDP::Address::from_string(ip), port),
        Network::request("create-room"));
}

Create::~Create()
{
}

void Create::load()
{
    _registry.run_systems();
}
