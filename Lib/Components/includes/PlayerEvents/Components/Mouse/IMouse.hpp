#ifndef __IMOUSE__
#define __IMOUSE__

#include "Physics2D/Components/Position.hpp"

class IMouse {
  public:
    virtual ~IMouse() = default;

    virtual bool isLeftButtonMousePressed() const = 0;
    virtual Position::Data getMousePosition() const = 0;
};

#endif /* __IMOUSE__ */