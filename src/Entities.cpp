#include <Entities.h>

namespace physics
{

void PhysicsEntity::update(const tile::TileMap& tile_map,
                           const Vector2& movement,
                           const float& deltaTime)
{
    Vector2 frame_movement = { movement.x + velocity_.x, movement.y + velocity_.y };

    velocity_.y = std::min(5.0F, velocity_.y + 0.1F);

    std::vector<Rectangle> tiles = tile_map.physicsTilesArround(box_.x, box_.y);

    box_.x += frame_movement.x * speed_ * deltaTime;
    for (auto& tile : tiles) {
        if (CheckCollisionRecs(tile, box_)) {
            if (frame_movement.x > 0) {
                box_.x = tile.x - box_.width;
            } else {
                box_.x = tile.x + tile.width;
            }
        }
    }

    box_.y += frame_movement.y * speed_ * deltaTime;
    for (auto& tile : tiles) {
        if (CheckCollisionRecs(tile, box_)) {
            if (frame_movement.y > 0) {
                box_.y = tile.y - box_.height;
                velocity_.y = 0;
            } else {
                box_.y = tile.y + tile.height;
                velocity_.y = 0;
            }
        }
    }
}

void PhysicsEntity::render(Texture2D texture) const
{
    DrawTexture(texture, static_cast<int>(box_.x), static_cast<int>(box_.y), WHITE);
}

}  // namespace physics
