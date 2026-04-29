#include <Camera.h>
#include <raylib.h>

#include <cmath>

namespace raylib_ex
{

Camera2DEx::Camera2DEx(const Vector2& offset,
                       const Vector2& target,
                       const float& rotation,
                       const float& zoom)
    : raw_ { offset, target, rotation, zoom }
{
}

void Camera2DEx::update(const physics::PhysicsEntity& player,
                        const tile::TileMap& tile_map,
                        const float& delta,
                        const int& screen_width,
                        const int& screen_height)
{
    switch (mode_) {
    case FOLLOW: {
        static float min_effect_length = 4;
        static float fraction_speed = 2.0F;

        raw_.offset = (Vector2) { static_cast<float>(screen_width) / 2.0F,
                                  static_cast<float>(screen_height) / 2.0F };
        Vector2 diff { .x = player.box().x + (player.box().width / 2) - raw_.target.x,
                       .y = player.box().y + (player.box().height / 2) - raw_.target.y };

        float length { std::hypot(diff.x, diff.y) };

        if (length > min_effect_length) {
            raw_.target.x += diff.x * fraction_speed * delta;
            raw_.target.y += diff.y * fraction_speed * delta;
        }
        break;
    }

    default:
        break;
    }
};

}  // namespace raylib_ex
