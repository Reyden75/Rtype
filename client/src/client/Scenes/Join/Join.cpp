#include "Scenes/Join.hpp"
#include "GameObject/Menu/Backgrounds/Background.hpp"
#include "GameObject/Menu/Buttons/Button.hpp"
#include "GameObject/Menu/Decors/Decor.hpp"
#include "Scenes/Game.hpp"

Join::Join(std::stack<std::unique_ptr<IScene>> &scenes, const std::string &ip,
    const int &port)
    : _scenes(scenes), _udpService(Router({Route("confirm-get-rooms",
                           [this, ip, port](const Network::request &req,
                               const Network::response &res) {
                               confirmGetRooms(req);
                               createJoinButtons(ip, port);
                           })}))
{
    _udpService.listenAsync();
    _udpService.send(UDP::Endpoint(UDP::Address::from_string(ip), port),
        Network::request("get-rooms"));
}

Join::~Join()
{
}

void Join::load()
{
    _registry.run_systems();
}

void Join::createJoinButtons(const std::string &ip, const int &port)
{
    Button lobbyButton;
    Position::Data pos = {867, 100};

    lobbyButton.init(_registry, _assetsManager);
    for (int roomId : _rooms) {
        pos.y += 200;
        lobbyButton.create(
            _registry, _scenes, ip, port, pos,
            {static_cast<int>(pos.x), static_cast<int>(pos.y), 1053, 342},
            [this, ip, port, roomId]() {
                _scenes.push(std::make_unique<Game>(ip, port, roomId));
            },
            _assetsManager, "sprites/join_btn.png");
    }
}

void Join::confirmGetRooms(const Network::request &req)
{
    size_t idx = 0;
    int tmp;

    std::cout << "Start" << std::endl;

    std::memcpy(&tmp, &req.body[idx], sizeof(int));
    if (tmp == -1) {
        return;
    }
    _rooms.push_back(tmp);
    idx += sizeof(int);

    std::memcpy(&tmp, &req.body[idx], sizeof(int));
    if (tmp == -1) {
        return;
    }
    _rooms.push_back(tmp);
    idx += sizeof(int);

    std::memcpy(&tmp, &req.body[idx], sizeof(int));
    if (tmp == -1) {
        return;
    }
    _rooms.push_back(tmp);
    idx += sizeof(int);

    std::memcpy(&tmp, &req.body[idx], sizeof(int));
    if (tmp == -1) {
        return;
    }
    _rooms.push_back(tmp);
    idx += sizeof(int);

    std::memcpy(&tmp, &req.body[idx], sizeof(int));
    if (tmp == -1) {
        return;
    }
    _rooms.push_back(tmp);
    idx += sizeof(int);

    std::cout << "End" << std::endl;
}
