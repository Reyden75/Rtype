#ifndef __CREATE__
#define __CREATE__

#include <stack>

#include "IScene.hpp"
#include "Network.hpp"
#include "Renderer/AssetsManager.hpp"
#include "UDP.hpp"
#include "registry.hpp"

class Create : public IScene {
  public:
    Create(std::stack<std::unique_ptr<IScene>> &, const std::string &,
        const int &, const AssetsManager &);
    ~Create();

    void load();
    void createList(const std::string &, const std::string &,
        const std::function<void()> &);

  private:
    registry _registry;
    std::stack<std::unique_ptr<IScene>> &_scenes;
    AssetsManager _assetsManager;
    UDP::Service _udpService;
};

#endif