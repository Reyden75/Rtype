#ifndef __IWINDOW__
#define __IWINDOW__

#include "Renderer/Components/Sprite/ISprite.hpp"

class IWindow {
  public:
    virtual ~IWindow() = default;

    virtual bool isOpen() const = 0;
    virtual void clear() = 0;
    virtual bool isEventClose() const = 0;
    virtual bool isEventButtonPressed() const = 0;
    virtual bool isEventKeyReleased() const = 0;
    virtual bool isKeyEnterCode() const = 0;
    virtual bool isKeySpaceCode() const = 0;
    virtual void display() = 0;
    virtual void close() = 0;
    virtual void updateEvents() = 0;
    virtual void draw(std::shared_ptr<ISprite>) = 0;
};

#endif /* __IWINDOW__ */