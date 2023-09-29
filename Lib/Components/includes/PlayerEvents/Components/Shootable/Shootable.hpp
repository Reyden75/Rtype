// #ifndef __SHOOTABLE__
// #define __SHOOTABLE__

// #include <SFML/System/Clock.hpp>
// #include <SFML/Window/Keyboard.hpp>

// #include "game/physics2D.hpp"
// #include "game/rendering.hpp"
// #include "game/specifications.hpp"
// #include "game/window.hpp"

// namespace component
// {
//     struct shootable {
//         bool isShoot()
//         {
//             if (_clock.getElapsedTime().asSeconds() > 0.25) {
//                 _clock.restart();
//                 return sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
//             }
//             return false;
//         };
//         void createBullet(registry &r, const sf::Vector2f &position)
//         {
//             const entity &e = r.spawn_entity();

//             Physics2D::initBullet(r, e, position);
//             Rendering::initBullet(r, e, position);
//             Specifications::initBullet(r, e);
//         };
//         sf::Clock _clock = sf::Clock();
//     };
// } // namespace component

// #endif /* __SHOOTABLE__ */