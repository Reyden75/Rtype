#ifndef __IPARSER__
#define __IPARSER__

#include <iostream>
#include <map>
#include <string>
#include <tinyxml.h>
#include <vector>
#include "../../Components/includes/Physics2D/Components/HitBox.hpp"

namespace Game
{
    enum Difficulties { Easy, Normal, Hard, Survive };
    enum Patterns { Horizontal, Vertical, Snake };
    enum Obstacles { None = 0, Little = 60, Many = 180, Forcefield = 300 };

    const std::map<std::string, Game::Difficulties> _DifficultyMap = {
        {"Easy", Easy}, {"Normal", Normal}, {"Hard", Hard},
        {"Survive", Survive}};

    const std::map<std::string, Game::Patterns> _PatternMap = {
        {"Horizontal", Horizontal}, {"Vertical", Vertical}, {"Snake", Snake}};

    struct enemy {
        // stats
        std::string _name;
        int _hp;
        float _velocity;
        Patterns _pattern;
        // spawn
        int _spawnInterval;
        int _appearanceTime;
        int _duration;
        // abilities
        bool _shooting;
        int _damage;
        // sprites
        std::string _sprite;
        std::string _shootingSprite;
        HitBox::Data rect;
    };
}; // namespace Game

/**
 * @brief Interface for a parser that can parse game settings and enemies from a file.
*/

class IParser {
  public:
    ~IParser() = default;
    virtual void setPath(const std::string &path) = 0;
    virtual void init() = 0;
    virtual bool setSettings() = 0;
    virtual bool setEnemies() = 0;
    virtual std::vector<Game::enemy> &getEnemies() = 0;
};

#endif