#include "Server.hpp"

int main()
{
    try {
        Server().run();
    } catch (const std::runtime_error &e) {
        std::cout << "ERRRO: " << e.what() << std::endl;
    }
}
