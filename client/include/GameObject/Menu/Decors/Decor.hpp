#ifndef _DECOR_
#define _DECOR_

#include <memory>
#include <stack>
#include "GameObject/IGameObject.hpp"
#include "IScene.hpp"
#include "Renderer/AssetsManager.hpp"

class Decor : public IGameObject {
  public:
    Decor();
    ~Decor() = default;

    void init(registry &r, AssetsManager &assets);
    void create(registry &r, const Position::Data &pos,
        AssetsManager &assetsManager, const std::string &path);
    void createMoving(registry &r, const Position::Data &pos,
        const Velocity::Data &vel, AssetsManager &assetsManager,
        const std::string &path);
};

#endif