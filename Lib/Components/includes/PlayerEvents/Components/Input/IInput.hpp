#ifndef __IINPUT__
#define __IINPUT__

class IInput {
  public:
    virtual ~IInput() = default;

    virtual bool isKeyPressed(const int &) const = 0;
    virtual bool isKeyZ() const = 0;
    virtual bool isKeyQ() const = 0;
    virtual bool isKeyS() const = 0;
    virtual bool isKeyD() const = 0;
    virtual bool isKeySpace() const = 0;
    virtual bool isKeyEnter() const = 0;
};

#endif /* __IINPUT__ */