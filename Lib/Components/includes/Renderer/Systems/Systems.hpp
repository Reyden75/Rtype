#ifndef __SYSTEMS_RENDERER__
#define __SYSTEMS_RENDERER__

#include "Renderer/Components/Drawable.hpp"
#include "registry.hpp"

namespace Systems
{
    namespace Renderer
    {
        class Draw {
          public:
            void operator()(registry &r,
                sparse_array<Drawable::Component> &drawables,
                sparse_array<Position::Component> &positions) const
            {
                for (size_t i = 0;
                     i < drawables.size() && i < positions.size(); i++) {
                    auto &draw = drawables[i];
                    auto &pos = positions[i];
                    if (draw.has_value() && pos.has_value()) {
                        draw.value().updatePosition(pos.value().getData());
                        draw.value().draw();
                    }
                }
            };
        };

        class MoveFstBackground {
          public:
            void operator()(registry &r,
                sparse_array<Drawable::Component> &drawables,
                sparse_array<Position::Component> &positions) const
            {
                for (size_t i = 0;
                     i < drawables.size() && i < positions.size(); i++) {
                    auto &draw = drawables[i];
                    auto &pos = positions[i];

                    if (draw.has_value()) {
                        SpriteDimensions dim =
                            draw.value().getSpriteDimensions();

                        if (dim.width > 1920 && draw.has_value()
                            && pos.has_value()) {
                            if (pos.value().getData().x < -dim.width) {
                                draw.value().updatePosition({2560, 0});
                                pos.value().update({dim.width, 0});
                            }
                            draw.value().draw();
                        }
                    }
                }
            };
        };

        class MoveSndBackground {
          public:
            void operator()(registry &r,
                sparse_array<Drawable::Component> &drawables,
                sparse_array<Position::Component> &positions) const
            {
                for (size_t i = 0;
                     i < drawables.size() && i < positions.size(); i++) {
                    auto &draw = drawables[i];
                    auto &pos = positions[i];

                    if (draw.has_value()) {
                        SpriteDimensions dim =
                            draw.value().getSpriteDimensions();

                        if (dim.width > 1920 && draw.has_value()
                            && pos.has_value()) {
                            if (pos.value().getData().x < -2510) {
                                draw.value().updatePosition({1920, 0});
                                pos.value().update({1920, 0});
                            }
                            draw.value().updatePosition(pos.value().getData());
                            draw.value().draw();
                        }
                    }
                }
            };
        };
    }; // namespace Renderer
};     // namespace Systems
#endif /* __SYSTEMS_RENDERER__ */