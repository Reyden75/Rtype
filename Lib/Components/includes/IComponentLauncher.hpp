#ifndef __ICOMPONENT_LAUNCHER__
#define __ICOMPONENT_LAUNCHER__

#include "registry.hpp"

class IComponentLauncher {
  public:
    virtual ~IComponentLauncher() = default;
    virtual void init(registry &) = 0;
};

#endif /* __ICOMPONENT_LAUNCHER__ */