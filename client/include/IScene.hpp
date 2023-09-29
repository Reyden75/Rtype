#ifndef __ISCENE__
#define __ISCENE__

class IScene {
  public:
    virtual ~IScene() = default;

    virtual void load() = 0;
};

#endif