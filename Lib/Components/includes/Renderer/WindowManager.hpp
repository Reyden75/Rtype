#ifndef __WINDOW_MANAGER__
#define __WINDOW_MANAGER__

#include <iostream>

#include "IComponent.hpp"
#include "Renderer/Components/Window/IWindow.hpp"
#include "Renderer/Components/Window/WindowSFML.hpp"

class WindowManager {
    using ScreenType = const int &;

  public:
    WindowManager(ScreenType width, ScreenType height)
    {
        if (!window) {
            window = std::make_shared<WindowSFML>(width, height);
        }
    };
    ~WindowManager() = default;

    void destroyWindow()
    {
        std::cout << "WindowManager destroyed" << std::endl;
        window.reset();
    }

    static std::shared_ptr<IWindow> window;
};

inline std::shared_ptr<IWindow> WindowManager::window = nullptr;

#endif /* __WINDOW_MANAGER__ */