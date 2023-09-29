#ifndef __UDP_RECEIVER__
#define __UDP_RECEIVER__

#include <asio.hpp>
#include <vector>
#include "Network.hpp"
#include "Router.hpp"

namespace UDP
{
    using Request = const Network::request &;
    using Endpoint = asio::ip::udp::endpoint;
    using Address = asio::ip::address;
    using Socket = asio::ip::udp::socket;
    using IOContext = asio::io_context;

    class Service {
      public:
        Service(const Router &router = Router(), const int &port = 0);
        ~Service();
        void listen();
        void listenAsync();
        void send(const Endpoint &, Request);
        void receive(Socket &socket, Router &router);

      private:
        IOContext _ioContext;
        Router _router;
        Socket _socket;
        std::thread _udpThread;
        bool _stopRequested = false;

    };
}; // namespace UDP

#endif /* __UDP_RECEIVER__ */