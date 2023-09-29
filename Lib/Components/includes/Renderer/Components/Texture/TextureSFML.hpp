#ifndef __TEXTURE_SFML__
#define __TEXTURE_SFML__

#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include "Renderer/Components/Texture/ITexture.hpp"

class TextureSFML : public ITexture {
  public:
    TextureSFML(const std::string &path) : _path(path){};
    ~TextureSFML()
    {
        std::cout << "Destroying TextureSFML" << std::endl;
    };

    bool loadFromFile() override
    {
        return _texture.loadFromFile(_path);
    };

    const sf::Texture *getTexture() const
    {
        return &_texture;
    }

  private:
    const std::string _path;
    sf::Texture _texture;
};

#endif /* __TEXTURE_SFML__ */