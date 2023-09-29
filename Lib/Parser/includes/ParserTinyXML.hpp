#ifndef __TINY_XML_PARSER__
#define __TINY_XML_PARSER__

#include <iostream>
#include <tinyxml.h>
#include "./IParser.hpp"

/**
 * @brief A parser for parsing XML files containing information about game
 * levels and enemies.
 * @details This parser uses the TinyXML2 library to parse XML files containing
 * information about game levels and enemies. It extracts the necessary
 * information from the XML files and creates `Game::enemy` objects.
 */

class TinyXMLParser : public IParser {
  public:
    /**
     * @brief Constructs a TinyXMLParser object with the given path to the XML
     * file.
     * @param path The path to the XML file to be parsed.
     */
    TinyXMLParser(const std::string &path) : _path(path)
    {
    }

    /**
     * @brief Destructor for the TinyXMLParser object.
     */
    ~TinyXMLParser()
    {
        std::cout << "Destroying TinyXMLParser" << std::endl;
    }

    /**
     * @brief Sets the path of the XML file to be parsed.
     * @param path The path to the XML file to be parsed.
     */
    void setPath(const std::string &path) override
    {
        _path = path;
    }

    /**
     * @brief Initializes the parser by setting the game settings and enemies.
     * If the settings or enemies loading fails, an appropriate message is
     * displayed.
     */
    void init() override
    {
        // Set the game settings from the XML file
        if (!setSettings())
            std::cout << "Settings loading failed" << std::endl;

        // Set the enemies from the XML file
        if (!setEnemies())
            std::cout << "Enemies loading failed" << std::endl;
    }

    /**
     * @brief Parses the XML file and sets the game settings accordingly.
     * @return A boolean indicating whether the settings were successfully set.
     */
    bool setSettings() override
    {
        // Load the XML document from the file
        TiXmlDocument doc(_path);
        if (!doc.LoadFile()) {
            std::cout << "Couldn't Load Document : " << _path << std::endl;
            return false;
        }

        // Get the root element of the document
        TiXmlHandle hld(&doc);

        // Find the "map" element under "settings" under "general"
        TiXmlElement *settings = hld.FirstChildElement("general")
                                     .FirstChildElement("settings")
                                     .FirstChildElement("map")
                                     .ToElement();

        // Check if the "map" element was found
        if (!settings) {
            std::cout << "Bad XML Format." << std::endl;
            return false;
        }

        // Set the game settings from the attributes of the "map" element
        std::string difficulty;
        settings->QueryIntAttribute("level", &_level);
        settings->QueryIntAttribute("players", &_players);
        settings->QueryIntAttribute("duration", &_duration);
        settings->QueryStringAttribute("difficulty", &difficulty);
        setDifficulty(difficulty);
        settings->QueryBoolAttribute("boss", &_boss);

        return true;
    }

    // Sets the enemies from the XML file
    bool setEnemies() override
    {
        // Load the XML document from the file
        TiXmlDocument doc(_path);
        if (!doc.LoadFile()) {
            std::cout << "Couldn't Load Document : " << _path << std::endl;
            return false;
        }

        // Get the root element of the document
        TiXmlHandle hld(&doc);

        // Find the "enemies" element under "general"
        TiXmlElement *enemies = hld.FirstChildElement("general")
                                    .FirstChildElement("enemies")
                                    .ToElement();

        // Find the first "enemy" element under "enemies"
        TiXmlElement *enemy = enemies->FirstChildElement("enemy");

        // Check if the "enemies" and "enemy" elements were found
        if (!enemies || !enemy) {
            std::cout << "Bad XML Format." << std::endl;
            return false;
        }

        // Iterate over all the "enemy" elements and set their attributes
        while (enemy) {
            Game::enemy e = {};
            setStats(e, *enemy, "stats");
            setSpawn(e, *enemy, "spawn");
            setAbility(e, *enemy, "ability");
            setSprites(e, *enemy, "sprites");
            _enemies.push_back(e); // Push the created structure into the vector 
            enemy = enemy->NextSiblingElement("enemy");
        }
        return true;
    }

     /**
     * @brief Sets the difficulty level of the game.
     * @param difficulty The difficulty level of the game as a string.
     */

    void setDifficulty(const std::string &difficulty)
    {
        for (auto &DiffCouple : Game::_DifficultyMap)
            if (difficulty.compare(DiffCouple.first) == 0) {
                _difficulty = DiffCouple.second;
                return;
            }
    }

     /**
     * @brief Sets the pattern for an enemy.
     * @param e The enemy for which to set the pattern.
     * @param pattern The pattern to set for the enemy.
     */

    void setPattern(Game::enemy &e, const std::string &pattern)
    {
        for (auto &PatCouple : Game::_PatternMap)
            if (pattern.compare(PatCouple.first) == 0) {
                e._pattern = PatCouple.second;
                break;
            }
    }

     /**
     * @brief Sets the stats for an enemy.
     * @param e The enemy for which to set the stats.
     * @param enemy The XML element containing the enemy information.
     * @param elem The name of the XML element containing the stats
     * information.
     */

    void setStats(
        Game::enemy &e, const TiXmlElement &enemy, const std::string &elem)
    {
        std::string pattern;

        enemy.FirstChildElement(elem)->QueryStringAttribute("name", &e._name);
        enemy.FirstChildElement(elem)->QueryIntAttribute("hp", &e._hp);
        enemy.FirstChildElement(elem)->QueryFloatAttribute(
            "velocity", &e._velocity);
        enemy.FirstChildElement(elem)->QueryStringAttribute(
            "pattern", &pattern);
        setPattern(e, pattern);
    }

     /**
     * @brief Sets the spawn information for an enemy.
     * @param e The enemy for which to set the spawn information.
     * @param enemy The XML element containing the enemy information.
     * @param elem The name of the XML element containing the spawn
     * information.
     */

    void setSpawn(
        Game::enemy &e, const TiXmlElement &enemy, const std::string &elem)
    {
        enemy.FirstChildElement(elem)->QueryIntAttribute(
            "appearanceTime", &e._appearanceTime);
        enemy.FirstChildElement(elem)->QueryIntAttribute(
            "spawnInterval", &e._spawnInterval);
        enemy.FirstChildElement(elem)->QueryIntAttribute(
            "duration", &e._duration);
        enemy.FirstChildElement(elem)->QueryIntAttribute("left", &e.rect.left);
        enemy.FirstChildElement(elem)->QueryIntAttribute("top", &e.rect.top);
        enemy.FirstChildElement(elem)->QueryIntAttribute(
            "width", &e.rect.width);
        enemy.FirstChildElement(elem)->QueryIntAttribute(
            "height", &e.rect.height);
    }

     /**
     * @brief Sets the ability information for an enemy.
     * @param e The enemy for which to set the ability information.
     * @param enemy The XML element containing the enemy information.
     * @param elem The name of the XML element containing the ability
     * information.
     */

    void setAbility(
        Game::enemy &e, const TiXmlElement &enemy, const std::string &elem)
    {
        enemy.FirstChildElement(elem)->QueryBoolAttribute(
            "shooting", &e._shooting);
        enemy.FirstChildElement(elem)->QueryIntAttribute("damage", &e._damage);
    }

    /**
     * @brief Sets the sprite information for an enemy.
     * @param e The enemy for which to set the sprite information.
     * @param enemy The XML element containing the enemy information.
     * @param elem The name of the XML element containing the sprite
     * information.
     */

    void setSprites(
        Game::enemy &e, const TiXmlElement &enemy, const std::string &elem)
    {
        enemy.FirstChildElement(elem)->QueryStringAttribute(
            "sprite", &e._sprite);
        enemy.FirstChildElement(elem)->QueryStringAttribute(
            "shootingSprite", &e._shootingSprite);
        enemy.FirstChildElement(elem)->QueryIntAttribute("left", &e.rect.left);
        enemy.FirstChildElement(elem)->QueryIntAttribute("top", &e.rect.top);
        enemy.FirstChildElement(elem)->QueryIntAttribute(
            "width", &e.rect.width);
        enemy.FirstChildElement(elem)->QueryIntAttribute(
            "height", &e.rect.height);
    }

     /**
     * @brief Returns a vector of enemies created from the parsed XML file.
     * @return A vector of `Game::enemy` objects created from the parsed XML
     * file.
     */

    std::vector<Game::enemy> &getEnemies() override
    {
        return _enemies;
    }

  private:
    int _level;                     ///< The level number.
    int _players;                   ///< The number of players.
    int _duration;                  ///< The duration of the level in seconds.
    Game::Difficulties _difficulty; ///< The difficulty level.
    bool _boss;        ///< Indicates whether the level has a boss.
    std::string _path; ///< The path of the XML file to be parsed.
    std::vector<Game::enemy>
        _enemies; ///< A vector of enemies created from the parsed XML file.};
};

#endif