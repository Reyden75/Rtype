#ifndef __CLIENT_MANAGER__
#define __CLIENT_MANAGER__

#include <stack>
#include "Scenes/Game.hpp"
#include "Scenes/Menu.hpp"
#include "UDP.hpp"

class SceneManager {
  public:
    SceneManager();
    ~SceneManager();

    void loadScene();
    void run(const std::string &ip = "127.0.0.1",
        const unsigned short &port = 8080);

  private:
    std::unique_ptr<WindowManager> _windowManager;
    std::stack<std::unique_ptr<IScene>> _scenes;
};

#endif /* __CLIENT_MANAGER__ */