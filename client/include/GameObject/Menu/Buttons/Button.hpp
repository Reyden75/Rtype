#ifndef _BUTTON_
#define _BUTTON_

#include <memory>
#include <stack>
#include "GameObject/IGameObject.hpp"
#include "IScene.hpp"
#include "Renderer/AssetsManager.hpp"

class Button {
  public:
    Button();
    ~Button() = default;

    void init(registry &r, AssetsManager &assets);
    void create(registry &r, std::stack<std::unique_ptr<IScene>> &scenes,
        const std::string &ip, const int &port, const Position::Data &pos,
        const HitBox::Data &hb, const std::function<void()> &onClick,
        AssetsManager &assetsManager, const std::string &path);
};

#endif