#ifndef __ICOMPONENT__
#define __ICOMPONENT__

#include <memory>

class IComponent {
  public:
    virtual ~IComponent() = default;
    virtual std::unique_ptr<char[]> toBuffer() const = 0;
};

#endif /* __ICOMPONENT__ */