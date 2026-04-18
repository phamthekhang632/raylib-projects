#include <Entities.h>

PhysicsEntity::PhysicsEntity(std::string type, Vector2 position, Vector2 size)
    : type_(std::move(type)), position_(std::move(position)), size_(std::move(size)) { };

PhysicsEntity::~PhysicsEntity() = default;

void PhysicsEntity::update(Vector2 movement, double deltaTime)
{
    Vector2 frame_movement = { movement.x + velocity_.x, movement.y + velocity_.y };

    position_.x += frame_movement.x * speed_ * deltaTime;
    position_.y += frame_movement.y * speed_ * deltaTime;
}

void PhysicsEntity::render(Texture2D texture)
{
    DrawTextureEx(texture, position_, 0.0f, 2.0f, WHITE);
}
