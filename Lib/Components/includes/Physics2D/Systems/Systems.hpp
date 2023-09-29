#ifndef __SYSTEMS_PHYSICS2D__
#define __SYSTEMS_PHYSICS2D__

#include "Physics2D/Components/HitBox.hpp"
#include "Physics2D/Components/Position.hpp"
#include "Physics2D/Components/Velocity.hpp"
#include "registry.hpp"

namespace Systems
{
    namespace Physics2D
    {
        class UpdatePosition {
          public:
            void operator()(registry &r,
                sparse_array<Position::Component> &positions,
                sparse_array<Velocity::Component> &velocities) const
            {
                for (size_t i = 0;
                     i < positions.size() && i < velocities.size(); ++i) {
                    auto &pos = positions[i];
                    auto &vel = velocities[i];
                    if (pos.has_value() && vel.has_value()) {
                        std::chrono::time_point<
                            std::chrono::high_resolution_clock>
                            now = std::chrono::high_resolution_clock::now();
                        std::chrono::time_point<
                            std::chrono::high_resolution_clock>
                            lastUpdate = pos.value().getLastUpdate();

                        auto elapsed = now - lastUpdate;
                        auto velData = vel.value().getData();

                        Velocity::Data velocity = {
                            velData.x
                                * (std::chrono::duration_cast<
                                       std::chrono::nanoseconds>(elapsed)
                                        .count()
                                    / 1000000000.0f),
                            velData.y
                                * (std::chrono::duration_cast<
                                       std::chrono::nanoseconds>(elapsed)
                                        .count()
                                    / 1000000000.0f),
                        };
                        pos.value().update(velocity, now);
                    }
                }
            };
        };

        class OutOfBound {
          public:
            void operator()(registry &r,
                sparse_array<Position::Component> &positions) const
            {
                for (size_t i = 0; i < positions.size(); ++i) {
                    auto &pos = positions[i];
                    if (pos.has_value()) {
                        if (pos.value().isOutOfBound()) {
                            r.kill_entity(r.entity_from_index(i));
                        }
                    }
                }
            };
        };

        class Collide {
          public:
            void operator()(registry &r,
                sparse_array<HitBox::Component> &hitBoxes,
                sparse_array<Position::Component> &positions) const
            {
                for (size_t i = 0; i < hitBoxes.size(); ++i) {
                    auto &hitBox = hitBoxes[i];
                    auto &position = positions[i];
                    if (hitBox.has_value() && position.has_value()) {
                        auto &hitBoxValue = hitBox.value();
                        auto positionData = position.value().getData();
                        hitBoxValue.update(positionData.x, positionData.y);
                        for (size_t j = i + 1; j < hitBoxes.size(); ++j) {
                            auto &hitBox2 = hitBoxes[j];
                            auto &position2 = positions[j];
                            if (hitBox2.has_value() && position2.has_value()) {
                                auto &hitBoxValue2 = hitBox2.value();
                                auto positionData2 = position2.value().getData();
                                hitBoxValue2.update(
                                    positionData2.x, positionData2.y);

                                if (hitBoxValue.isColliding(
                                        hitBoxValue2.getData())) {
                                    hitBoxValue.execute(j);
                                    hitBoxValue2.execute(i);
                                }
                            }
                        }
                    }
                }
            };
        };
    }; // namespace Physics2D
};     // namespace Systems

#endif /* __SYSTEMS_PHYSICS2D__ */