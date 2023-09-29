#ifndef _BACKGROUND_
#define _BACKGROUND_

#include <memory>
#include <stack>
#include "GameObject/IGameObject.hpp"
#include "IScene.hpp"
#include "Renderer/AssetsManager.hpp"

class Background : public IGameObject {
  public:
    Background() = default;
    ~Background() = default;

    void init(registry &r, AssetsManager &assets);
    void createFst(registry &r, const Position::Data &pos,
        const Velocity::Data &vel, AssetsManager &assetsManager,
        const std::string &path);
    void createSnd(registry &r, const Position::Data &pos,
        const Velocity::Data &vel, AssetsManager &assetsManager,
        const std::string &path);
};

#endif