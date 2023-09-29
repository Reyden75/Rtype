#ifndef __NETWORK__
#define __NETWORK__

#include <asio.hpp>
#include <iostream>

#include <cstring>
#include <ctime>
#include <functional>
#include <map>

namespace Network
{
    struct request {
        request() = default;

        request(const std::string &command,
            const std::map<void *, const std::size_t> &contents = {},
            size_t id = 0)
        {
            entityId = id;
            std::memcpy(cmd, command.c_str(), command.size());

            std::size_t idx = 0;
            for (auto [ptr, size] : contents) {
                std::memcpy(&body[idx], ptr, size);
                idx += size;
            }
        };
        size_t entityId = 0;
        char cmd[64] = {0};
        char body[1024] = {0};
    };

    struct response {
        asio::ip::udp::endpoint endpoint;
        std::function<void(request)> send;
    };
} // namespace Network

#endif // __NETWORK__
