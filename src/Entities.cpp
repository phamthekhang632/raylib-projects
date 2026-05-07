#include <Entities.h>

#include <cassert>

namespace physics
{

std::unique_ptr<std::unordered_map<std::string, std::vector<Texture2D>>> PhysicsEntity::textures =
    nullptr;
std::unique_ptr<std::unordered_map<std::string, Animation>> PhysicsEntity::animations = nullptr;

void PhysicsEntity::update(const environment::TileMap& tile_map,
                           const Vector2& movement,
                           const float& deltaTime)
{
    Vector2 frame_movement = { movement.x + velocity_.x, movement.y + velocity_.y };

    /* Gravity */
    velocity_.y = std::min(5.0F, velocity_.y + 0.1F);

    /* Collision */
    collisions_ = {
        {    "up", false },
        {  "down", false },
        {  "left", false },
        { "right", false }
    };
    std::vector<Rectangle> tiles = tile_map.physicsTilesArround(box_.x, box_.y);

    box_.x += frame_movement.x * speed_ * deltaTime;
    for (auto& tile : tiles) {
        if (CheckCollisionRecs(tile, box_)) {
            if (frame_movement.x > 0) {
                box_.x = tile.x - box_.width;
                collisions_["right"] = true;
            }
            if (frame_movement.x < 0) {
                box_.x = tile.x + tile.width;
                collisions_["left"] = true;
            }
        }
    }

    box_.y += frame_movement.y * speed_ * deltaTime;
    for (auto& tile : tiles) {
        if (CheckCollisionRecs(tile, box_)) {
            if (frame_movement.y > 0) {
                box_.y = tile.y - box_.height;
                velocity_.y = 0;
                collisions_["down"] = true;
            }
            if (frame_movement.y < 0) {
                box_.y = tile.y + tile.height;
                velocity_.y = 0;
                collisions_["up"] = true;
            }
        }
    }

    /* Animation */
    if (movement.x > 0) {
        face_left_ = false;
    } else if (movement.x < 0) {
        face_left_ = true;
    }

    animation_->update();
}

void PhysicsEntity::render() const
{
    DrawTexture(animation_->currentFrame(),
                static_cast<int>(box_.x),
                static_cast<int>(box_.y),
                WHITE);
}

Player::Player(Rectangle box) : PhysicsEntity("player", box) { }

void Player::update(const environment::TileMap& tile_map,
                    const Vector2& movement,
                    const float& deltaTime)
{
    PhysicsEntity::update(tile_map, movement, deltaTime);
    ++air_time_;

    if (PhysicsEntity::collisions().at("down")) {
        air_time_ = 0;
    }

    if (air_time_ > 4) {
        setAction("jump");
    } else if (movement.x != 0) {
        setAction("run");
    } else {
        setAction("idle");
    }
}

void Player::render()
{
    assert(PhysicsEntity::animation() != nullptr && "animation is not initialized");
    DrawTexture(PhysicsEntity::animation()->currentFrame(PhysicsEntity::faceLeft()),
                static_cast<int>(PhysicsEntity::box().x + PhysicsEntity::animationOffset().x),
                static_cast<int>(PhysicsEntity::box().y + PhysicsEntity::animationOffset().y),
                WHITE);
}

}  // namespace physics
