#ifndef __ROUTER__
#define __ROUTER__

#include <vector>
#include "Route.hpp"

class Router {
  private:
    const std::vector<Route> _routes = std::vector<Route>();

  public:
    Router();
    Router(const std::vector<Route> routes);
    ~Router();

    void launch(asio::ip::udp::socket &socket, Network::request req,
        asio::ip::udp::endpoint sender_endpoint) const;
};

#endif