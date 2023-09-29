#ifndef __SYSTEM_PLAYER_EVENTS__
#define __SYSTEM_PLAYER_EVENTS__

#include "Physics2D/Components/Velocity.hpp"
#include "PlayerEvents/Components/Clickable.hpp"
#include "PlayerEvents/Components/Controllable.hpp"
#include "registry.hpp"

namespace Systems
{
    namespace PlayerEvents
    {
        class Control {
          public:
            void operator()(registry &r,
                sparse_array<Controllable::Component> &controllables,
                sparse_array<Velocity::Component> &velocities) const
            {
                for (size_t i = 0;
                     i < controllables.size() && i < velocities.size(); ++i) {
                    auto &vel = velocities[i];
                    auto &ctrl = controllables[i];
                    if (vel.has_value() && ctrl.has_value()) {
                        ctrl.value().handleDirection();
                        vel.value().update(ctrl.value().getData());
                    }
                };
            };
        };

        class Shoot {
          public:
            void operator()(registry &r,
                sparse_array<Controllable::Component> &controllables) const
            {
                for (size_t i = 0; i < controllables.size(); ++i) {
                    auto &ctrl = controllables[i];
                    if (ctrl.has_value()) {
                        if (WindowManager::window->isEventKeyReleased()
                            && WindowManager::window->isKeySpaceCode())
                            ctrl.value().execute();
                    }
                };
            };
        };

        class ButtonClick {
          public:
            void operator()(registry &r,
                sparse_array<Clickable::Component> &clickables,
                sparse_array<HitBox::Component> &hitboxes) const
            {
                for (size_t i = 0;
                     i < clickables.size() && i < hitboxes.size(); ++i) {
                    auto &hb = hitboxes[i];
                    auto &clk = clickables[i];
                    if (hb.has_value() && clk.has_value()) {
                        if (clk.value().isClick(hb.value().getData())
                            && WindowManager::window->isEventButtonPressed()) {
                            clk.value().execute();
                        }
                    }
                };
            };
        };
    }; // namespace PlayerEvents
};     // namespace Systems

#endif /* __SYSTEM_PLAYER_EVENTS__ */