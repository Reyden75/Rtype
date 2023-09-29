#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "Renderer/AssetsManager.hpp"
#include "registry.hpp"

class IGameObject {
  public:
    virtual ~IGameObject() = default;

    virtual void init(registry &r, AssetsManager &assets) = 0;
};

#endif