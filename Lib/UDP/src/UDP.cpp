#include "UDP.hpp"
#include <algorithm>

UDP::Service::Service(const Router &router, const int &port)
    : _router(router),
      _socket(_ioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
{
}

UDP::Service::~Service()
{
    _stopRequested = true;
    if (_udpThread.joinable()) {
        _udpThread.join();
    }
}

void UDP::Service::receive(Socket &socket, Router &router)
{
    std::vector<Endpoint> connections = {};

    while (!_stopRequested) {
        char buff[sizeof(Network::request)] = {0};
        asio::ip::udp::endpoint sender_endpoint;

        try {
            socket.receive_from(asio::buffer(buff), sender_endpoint);
        } catch (const std::runtime_error &e) {
            std::cout << "[LOG] Exception" << e.what() << std::endl;
            return;
        }

        Network::request req;
        memcpy(&req, buff, sizeof(req));

        auto it =
            std::find(connections.begin(), connections.end(), sender_endpoint);

        if (it != connections.end()) {
            connections.emplace_back(sender_endpoint);
        }
        router.launch(socket, req, sender_endpoint);
    }
}

void UDP::Service::listen()
{
    receive(_socket, _router);
}

void UDP::Service::listenAsync()
{
    _udpThread = std::thread(&UDP::Service::receive, this, std::ref(_socket), std::ref(_router));
}

void UDP::Service::send(const Endpoint &endpoint, Request req)
{
    char buff[sizeof(req)] = {0};

    std::memcpy(buff, &req, sizeof(req));

    _socket.send_to(asio::buffer(buff), endpoint);
}
