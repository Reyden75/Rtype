#ifndef __ENTITY__
#define __ENTITY__

#include <cstddef>

class entity {
  public:
    friend class registry;

    operator std::size_t() const
    {
        return _size;
    }

  private:
    explicit entity(size_t size) : _size(size)
    {
    }
    const std::size_t _size;
};

#endif /* __ENTITY__ */
