#ifndef __ISPRITE__
#define __ISPRITE__

#include <string>

#include "Physics2D/Components/HitBox.hpp"
#include "Physics2D/Components/Position.hpp"
#include "Renderer/Components/Texture/ITexture.hpp"

struct SpriteDimensions {
    float left;
    float top;
    float width;
    float height;
};

class ISprite {
  public:
    virtual ~ISprite() = default;

    virtual void setTexture(std::shared_ptr <ITexture>) = 0;
    virtual void setPosition(const Position::Data &) = 0;
    virtual void setHitBox(const HitBox::Data &) = 0;
    virtual void setScale(const float &s = 1) = 0;
    virtual SpriteDimensions getSpriteDimensions() const = 0;
};

#endif /* __ISPRITE__ */