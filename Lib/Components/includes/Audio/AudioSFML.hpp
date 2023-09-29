#ifndef __AUDIO_SFML__
#define __AUDIO_SFML__

#include "IAudio.hpp"
#include <SFML/Audio.hpp>
#include <ostream>

class AudioSFML : public IAudio {
  public:
    ~AudioSFML()
    {
        std::cout << "Destroying AudioSFML" << std::endl;
    };

    bool loadFromFile(const std::string &path)
    {
        if (!_soundBuffer.loadFromFile(path)) {
            std::cout << "FAILED TO LOAD " << path << std::endl;
            return false;
        }
        _sound.setBuffer(_soundBuffer);
        return true;
    }

    void play()
    {
        _sound.play();
    }

    void stop()
    {
        _sound.stop();
    }

  private:
    sf::SoundBuffer _soundBuffer;
    sf::Sound _sound;
};

#endif /* __AUDIO_SFML__ */