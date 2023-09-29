#ifndef __MENU__
#define __MENU__

#include <stack>

#include "Audio/IAudio.hpp"
#include "IScene.hpp"
#include "Network.hpp"
#include "Renderer/AssetsManager.hpp"
#include "UDP.hpp"
#include "registry.hpp"

class Menu : public IScene {
  public:
    Menu(std::stack<std::unique_ptr<IScene>> &, const std::string &,
        const int &, std::function<void()>);
    ~Menu();

    void load();

  private:
    registry _registry;
    AssetsManager _assetsManager;
    std::stack<std::unique_ptr<IScene>> &_scenes;
    std::unique_ptr<IAudio> _audio;
};

#endif