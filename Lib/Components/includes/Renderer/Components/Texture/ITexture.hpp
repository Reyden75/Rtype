#ifndef __ITEXTURE__
#define __ITEXTURE__

class ITexture {
  public:
    virtual ~ITexture() = default;
    virtual bool loadFromFile() = 0;
};

#endif /* __ITEXTURE__ */