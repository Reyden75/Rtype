#include "Route.hpp"
#include <asio.hpp>

Route::Route(const std::string &route,
    std::function<void(
        const Network::request &req, const Network::response &res)>
        function)
    : _route(route), _function(function)
{
}

Route::~Route()
{
}

void Route::launchFunction(asio::ip::udp::socket &socket, Network::request req,
    asio::ip::udp::endpoint sender_endpoint) const
{
    Network::response res;

    res.send = [&socket, sender_endpoint](Network::request request) {
        asio::error_code ec;
        char body[sizeof(req)] = {0};

        memcpy(body, &request, sizeof(req));

        socket.send_to(asio::buffer(body), sender_endpoint);
    };

    res.endpoint = sender_endpoint;

    _function(req, res);
}

std::string Route::getRoute() const
{
    return _route;
}