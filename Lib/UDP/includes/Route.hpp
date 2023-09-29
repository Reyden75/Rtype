#ifndef __ROUTE__
#define __ROUTE__

#include <string>
#include <asio.hpp>
#include "Network.hpp"

class Route {
  private:
    const std::string _route;
    std::function<void(
        const Network::request &req, const Network::response &res)>
        _function;

  public:
    Route(const std::string &route,
        std::function<void(
            const Network::request &req, const Network::response &res)>);
    ~Route();

    std::string getRoute() const;
    void launchFunction(asio::ip::udp::socket &socket, Network::request req,
        asio::ip::udp::endpoint sender_endpoint) const;
};

#endif