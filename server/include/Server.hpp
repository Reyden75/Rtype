#ifndef __SERVER__
#define __SERVER__

#include "Room.hpp"
#include "UDP.hpp"

class Server {
    using Request = const Network::request &;
    using Response = const Network::response &;

  public:
    Server();
    ~Server() = default;

    void run();

  private:
    void join(Request, Response);
    void move(Request, Response);
    void shoot(Request, Response);
    void manageRoom(Request, Response);
    void sendRooms(Request, Response);
    void startGame(Request, Response);

    int createRoom();

    UDP::Service _udpService;

    int _roomId = 0;
    std::map<int, Room> _rooms;
};
#endif /* __SERVER__ */