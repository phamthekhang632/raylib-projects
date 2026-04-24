#include <Entities.h>

void PhysicsEntity::update(Vector2 movement, float deltaTime)
{
    Vector2 frame_movement = { movement.x + velocity_.x, movement.y + velocity_.y };

    box_.x += frame_movement.x * speed_ * deltaTime;
    box_.y += frame_movement.y * speed_ * deltaTime;

    velocity_.y = std::min(5.0F, velocity_.y + 0.1F);
}

void PhysicsEntity::render(Texture2D texture) const
{
    DrawTexture(texture, static_cast<int>(box_.x), static_cast<int>(box_.y), WHITE);
}
