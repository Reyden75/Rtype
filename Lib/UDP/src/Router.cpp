#include "Router.hpp"
#include <asio.hpp>
#include <iostream>

Router::Router()
{
}

Router::Router(const std::vector<Route> routes) : _routes(routes)
{
}

Router::~Router()
{
}

void Router::launch(asio::ip::udp::socket &socket, Network::request req,
    asio::ip::udp::endpoint sender_endpoint) const
{
    for (const Route &route : _routes) {
        if (req.cmd == route.getRoute()) {
            return route.launchFunction(socket, req, sender_endpoint);
        }
    }
    std::cout << req.cmd << " not found" << std::endl;
}