#ifndef __JOIN__
#define __JOIN__

#include <stack>

#include "IScene.hpp"
#include "Network.hpp"
#include "Renderer/AssetsManager.hpp"
#include "UDP.hpp"
#include "registry.hpp"

class Join : public IScene {
  public:
    Join(std::stack<std::unique_ptr<IScene>> &, const std::string &,
        const int &);
    ~Join();

    void load();
    void confirmGetRooms(const Network::request &);
    void createJoinButtons(const std::string &, const int &);

  private:
    registry _registry;
    AssetsManager _assetsManager;
    std::stack<std::unique_ptr<IScene>> &_scenes;
    UDP::Service _udpService;
    std::vector<int> _rooms;
};

#endif