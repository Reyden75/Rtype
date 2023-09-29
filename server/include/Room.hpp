#include <asio.hpp>
#include <chrono>
#include <memory>
#include <string>
#include <vector>
#include "Network.hpp"
#include "Physics2D/Physics2D.hpp"
#include "UDP.hpp"
#include "registry.hpp"

#include "IParser.hpp"
#include "ParserTinyXML.hpp"

class Room {
    using Endpoint = asio::ip::udp::endpoint;
    using Request = const Network::request &;
    using Response = const Network::response &;

  public:
    Room(UDP::Service &);
    ~Room();

    void sendToAll(Request);
    void sendToAllOthers(const Endpoint &, Request);
    void updateSystems();
    void startGame();

    void addClient(Response);
    void playerShoot(const size_t &);
    void updatePlayerPositions(
        const Controllable::Direction &, const size_t &);

    std::map<std::size_t, Endpoint> getClients() const;

    void spawnEnemy();
    void destroyEnemy();

  private:
    registry _registry;
    UDP::Service &_udpService;
    bool _isGameStarted = false;
    std::map<std::size_t, Endpoint> _clients;
    int _time;
    std::chrono::time_point<std::chrono::high_resolution_clock> _clock;
    std::shared_ptr<IParser> _parser;
};
