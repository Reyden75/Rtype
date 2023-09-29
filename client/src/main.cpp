#include "Scenes/SceneManager.hpp"

int main(int argc, char **argv)
{
    std::string ip = argc >= 2 ? argv[1] : "127.0.0.1";
    int port = argc >= 3 ? std::atoi(argv[2]) : 8080;

    // XInitThreads();

    try {
        SceneManager clientManager;

        clientManager.run(ip, port);
    } catch (const std::runtime_error &e) {
        std::cout << "Catch: " << e.what() << std::endl;
    }
    return 0;
}
