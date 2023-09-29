#include "Scenes/Menu.hpp"
#include "Audio/AudioSFML.hpp"

#include "GameObject/Menu/Backgrounds/Background.hpp"
#include "GameObject/Menu/Buttons/Button.hpp"
#include "GameObject/Menu/Decors/Decor.hpp"
#include "Physics2D/Physics2D.hpp"
#include "PlayerEvents/Components/Clickable.hpp"
#include "PlayerEvents/PlayerManager.hpp"
#include "Renderer/AssetsManager.hpp"
#include "Renderer/Components/Drawable.hpp"
#include "Scenes/Create.hpp"
#include "Scenes/Game.hpp"
#include "Scenes/Join.hpp"

Menu::Menu(std::stack<std::unique_ptr<IScene>> &scenes, const std::string &ip,
    const int &port, std::function<void()> exit)
    : _scenes(scenes), _audio(std::make_unique<AudioSFML>())
{
    _audio->loadFromFile("./sprites/menu.ogg");
    Button button;
    Background background;
    Decor decor;

    button.init(_registry, _assetsManager);
    background.init(_registry, _assetsManager);
    decor.init(_registry, _assetsManager);

    background.createFst(_registry, {0, 0}, {-250, 0}, _assetsManager,
        "sprites/background_menu.png");
    background.createSnd(_registry, {2510, 0}, {-250, 0}, _assetsManager,
        "sprites/reversed_background_menu.png");
    background.createFst(_registry, {2500, -750}, {-50, 0}, _assetsManager,
        "sprites/earth_planet.png");
    decor.createMoving(_registry, {1920, -500}, {-2500, 2500}, _assetsManager,
        "sprites/meteorite.png");
    button.create(
        _registry, _scenes, ip, port, {867, 425}, {867, 425, 200, 200},
        [this, ip, port]() {
            static bool isClicked = false;
            if (!isClicked) {
                isClicked = true;
                _scenes.push(std::make_unique<Join>(_scenes, ip, port));
            }
        },
        _assetsManager, "sprites/join_btn.png");
    button.create(
        _registry, _scenes, ip, port, {867, 625}, {867, 625, 825, 529},
        [this, ip, port]() {
            static bool isClicked = false;
            if (!isClicked) {
                isClicked = true;
                _scenes.push(std::make_unique<Create>(
                    _scenes, ip, port, _assetsManager));
            }
        },
        _assetsManager, "sprites/create_btn.png");
    button.create(
        _registry, _scenes, ip, port, {867, 825}, {867, 825, 1101, 742},
        [this, ip, port, exit]() {
            static bool isClicked = false;
            if (!isClicked) {
                isClicked = true;
                exit();
            }
        },
        _assetsManager, "sprites/exit_btn.png");
    decor.create(
        _registry, {610, 15}, _assetsManager, "sprites/r-type_title.png");
    _audio->play();
}

Menu::~Menu()
{
}

void Menu::load()
{
    // std::cout << _registry.get_components<Position::Component>()[0].value()
    //           << std::endl;
    _registry.run_systems();
}
