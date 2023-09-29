#ifndef __SYSTEMS__
#define __SYSTEMS__

namespace systems
{
    // class border_limits_system {
    //   public:
    //     void operator()(registry &r,
    //         sparse_array<component::position::system> &positions,
    //         sparse_array<component::controllable> &controllables,
    //         sparse_array<component::drawable> &drawables) const
    //     {
    //         for (size_t i = 0; i < positions.size() && i <
    //         controllables.size()
    //              && i < drawables.size();
    //              ++i) {
    //             auto &pos = positions[i];
    //             auto &ctrl = controllables[i];
    //             auto &draw = drawables[i];
    //             if (pos.has_value() && ctrl.has_value() && draw.has_value())
    //             {
    //                 // pos.value().setBorderLimits(
    //                 //     draw.value()._sprite.getGlobalBounds());
    //             }
    //         }
    //     };
    // };

    // class draw_system {
    //   public:
    //     void operator()(registry &r,
    //         sparse_array<component::drawable> &drawables,
    //         sparse_array<component::position::system> &positions) const
    //     {
    //         for (size_t i = 0; i < positions.size() && i < drawables.size();
    //              ++i) {
    //             auto &pos = positions[i];
    //             auto &draw = drawables[i];
    //             if (pos.has_value() && draw.has_value()) {
    //                 //
    //                 draw.value()._sprite.setPosition(pos.value()._position);
    //                 draw.value().draw();
    //             }
    //         };
    //     };
    // };

    // class control_system {
    //   public:
    //     void operator()(registry &r,
    //         sparse_array<component::controllable> &controllables,
    //         sparse_array<component::velocity> &velocities) const
    //     {
    //         for (size_t i = 0;
    //              i < controllables.size() && i < velocities.size(); ++i) {
    //             auto &vel = velocities[i];
    //             auto &ctrl = controllables[i];
    //             if (vel.has_value() && ctrl.has_value()) {
    //                 ctrl.value().handleInput();
    //                 vel.value()._velocity = ctrl.value()._velocityInput;
    //             }
    //         };
    //     };
    // };

    // class hitbox_system {
    //   public:
    //     void operator()(registry &r, sparse_array<component::hitBox>
    //     &hitBoxes,
    //         sparse_array<component::drawable> &drawables) const
    //     {
    //         for (size_t i = 0; i < hitBoxes.size() && i < drawables.size();
    //              ++i) {
    //             auto &cldbl = hitBoxes[i];
    //             auto &dwbl = drawables[i];
    //             if (cldbl.has_value() && dwbl.has_value()) {
    //                 cldbl.value().update(
    //                     dwbl.value()._sprite.getGlobalBounds());
    //             }
    //         }
    //     };
    // };

    // class damage_collide_system {
    //   public:
    //     void operator()(registry &r, sparse_array<component::hitBox>
    //     &hitBoxes,
    //         sparse_array<component::damage> &damages,
    //         sparse_array<component::health> &healths) const
    //     {
    //         for (size_t i = 0; i < hitBoxes.size() && i < damages.size();
    //              ++i) {
    //             auto &cld = hitBoxes[i];
    //             auto &dmg = damages[i];
    //             if (cld.has_value() && dmg.has_value()) {
    //                 for (size_t j = 0;
    //                      j < hitBoxes.size() && j < healths.size(); ++j) {
    //                     auto &cld2 = hitBoxes[j];
    //                     auto &hel = healths[j];
    //                     if (cld2.has_value() && hel.has_value()) {
    //                         if
    //                         (cld.value().isColliding(cld2.value()._hitBox))
    //                             hel.value().takeDamage(dmg.value()._damage);
    //                     }
    //                 }
    //             }
    //         }
    //     };
    // };

    // class shoot_system {
    //   public:
    //     void operator()(registry &r,
    //         sparse_array<component::shootable> &shootables,
    //         sparse_array<component::position::system> &positions) const
    //     {
    //         for (size_t i = 0; i < shootables.size() && i <
    //         positions.size();
    //              ++i) {
    //             auto &sht = shootables[i];
    //             auto &pos = positions[i];

    //             if (sht.has_value() && pos.has_value()) {
    //                 if (sht.value().isShoot()) {
    //                     // sht.value().createBullet(r,
    //                     pos.value()._position);
    //                 }
    //             }
    //         };
    //     };
    // };

    // class death_system {
    //   public:
    //     void operator()(
    //         registry &r, sparse_array<component::health> &healths) const
    //     {
    //         for (size_t i = 0; i < healths.size(); ++i) {
    //             auto &health = healths[i];
    //             if (health.has_value()) {
    //                 if (health.value()._health <= 0) {
    //                     r.kill_entity(r.entity_from_index(i));
    //                 }
    //             }
    //         }
    //     }
    // };
}; // namespace systems

#endif /* __SYSTEMS__ */