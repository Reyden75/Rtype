#include "Server.hpp"
#include <algorithm>
#include <map>
#include "Physics2D/Physics2D.hpp"
#include "PlayerEvents/Components/Controllable.hpp"

Server::Server()
    : _udpService(Router({Route("move",
                              [this](const Network::request &req,
                                  const Network::response &res) {
                                  move(req, res);
                              }),
                      Route("shoot",
                          [this](const Network::request &req,
                              const Network::response &res) {
                              shoot(req, res);
                          }),
                      Route("join",
                          [this](const Network::request &req,
                              const Network::response &res) {
                              join(req, res);
                          }),
                      Route("create-room",
                          [this](const Network::request &req,
                              const Network::response &res) {
                              manageRoom(req, res);
                          }),
                      Route("get-rooms",
                          [this](const Network::request &req,
                              const Network::response &res) {
                              sendRooms(req, res);
                          }),
                      Route("start-game",
                          [this](const Network::request &req,
                              const Network::response &res) {
                                startGame(req, res);
                          })}),
        8080)
{
}

void Server::run()
{
    std::cout << "Server is running !" << std::endl;
    _udpService.listenAsync();
    while (true) {
        for (auto &room : _rooms) {
            room.second.updateSystems();
        }
    }
}

int Server::createRoom()
{
    _rooms.emplace(++_roomId, Room(_udpService));
    return _roomId;
}

void Server::move(Request req, Response res)
{
    Controllable::Direction direction;
    std::memcpy(&direction, &req.body, sizeof(direction));

    for (auto &room : _rooms) {
        for (auto &client : room.second.getClients()) {
            if (client.second == res.endpoint) {
                room.second.updatePlayerPositions(direction, req.entityId);
            }
        }
    }
}

void Server::shoot(Request req, Response res)
{
    for (auto &room : _rooms) {
        for (auto &client : room.second.getClients()) {
            if (client.second == res.endpoint) {
                room.second.playerShoot(req.entityId);
            }
        }
    }
}

void Server::join(Request req, Response res)
{
    int roomId = 0;

    std::memcpy(&roomId, &req.body, sizeof(roomId));

    std::cout << "Try to join room " << roomId << std::endl;
    try {
        _rooms.at(roomId).addClient(res);
    } catch (const std::bad_optional_access &e) {
        std::cout << "Error : Room " << roomId << " doesn't exists."
                  << std::endl;
    }
}

void Server::manageRoom(Request req, Response res)
{
    try {
        std::cout << "Try to create room" << std::endl;
        int roomId = createRoom();
        res.send(Network::request(
            "confirm-create-room", {{&roomId, sizeof(roomId)}}));
        std::cout << "Room " << roomId << " created" << std::endl;
    } catch (const std::bad_optional_access &e) {
        std::cout << "Error : Failed to create room" << std::endl;
    }
}

void Server::sendRooms(Request req, Response res)
{
    int one = _rooms.size() > 0 ? 1 : -1;
    int two = _rooms.size() > 1 ? 2 : -1;
    int three = _rooms.size() > 2 ? 3 : -1;
    int four = _rooms.size() > 3 ? 4 : -1;
    int five = _rooms.size() > 4 ? 5 : -1;

    try {
        res.send(Network::request("confirm-get-rooms",
            {{&one, sizeof(one)}, {&two, sizeof(two)}, {&three, sizeof(three)},
                {&four, sizeof(four)}, {&five, sizeof(five)}}));
    } catch (const std::bad_optional_access &e) {
        std::cout << "Error : Failed to send rooms" << std::endl;
    }
}

void Server::startGame(Request req, Response res)
{
    for (auto &room : _rooms) {
        for (auto &client : room.second.getClients()) {
            if (client.second == res.endpoint) {
                room.second.startGame();
            }
        }
    }
}