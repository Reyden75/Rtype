#ifndef __IAUDIO__
#define __IAUDIO__

#include <string>

class IAudio {
  public:
    virtual ~IAudio() = default;
    virtual bool loadFromFile(const std::string &path) = 0;
    virtual void play() = 0;
    virtual void stop() = 0;
};

#endif /* __IAUDIO__ */