#ifndef __TAG__
#define __TAG__

#include "IComponent.hpp"

#include <cstring>
#include <iostream>
#include <memory>

namespace Tag
{
    struct Data {
        char tag[255];
    };

    class Component : public IComponent {
      public:
        Component(const std::string &tag) {
            std::memset(_tag.tag, 0, 255);
            std::memcpy(_tag.tag, tag.c_str(), tag.size());
        };
        Component(const Data &data) : _tag(data){};
        Component(const char *buffer)
        {
            std::memcpy(&_tag, buffer, sizeof(_tag));
        };

        Data getData() const
        {
            return _tag;
        };

        std::unique_ptr<char[]> toBuffer() const override
        {
            std::unique_ptr<char[]> binary = std::make_unique<char[]>(255);

            std::memcpy(binary.get(), &_tag, sizeof(_tag));
            return binary;
        }

      private:
        Data _tag;
    };
}; // namespace Tag

#endif /* __TAG__ */