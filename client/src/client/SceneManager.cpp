#include "Scenes/SceneManager.hpp"

SceneManager::SceneManager()
    : _windowManager(std::make_unique<WindowManager>(1920, 1080))
{
}

SceneManager::~SceneManager()
{
    _windowManager->destroyWindow();
}

void SceneManager::loadScene()
{
}

void SceneManager::run(const std::string &ip, const unsigned short &port)
{
    _scenes.push(std::make_unique<Menu>(_scenes, ip, port, [this]() {
        _windowManager->window->close();
    }));

    while (_windowManager->window->isOpen()) {
        _windowManager->window->updateEvents();
        _windowManager->window->clear();
        _scenes.top()->load();
        _windowManager->window->display();
        if (_windowManager->window->isEventClose())
            _windowManager->window->close();
    }
    std::cout << "Destroying window..." << std::endl;
}