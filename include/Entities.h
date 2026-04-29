#pragma once

#include <TileMap.h>
#include <raylib.h>

#include <string>
#include <vector>

namespace physics
{

class PhysicsEntity
{
public:
    PhysicsEntity() = default;

    PhysicsEntity(std::string type, Rectangle box) : type_(std::move(type)), box_(box) { };
    ~PhysicsEntity() = default;

    PhysicsEntity(const PhysicsEntity&) = delete;
    PhysicsEntity& operator=(const PhysicsEntity&) = delete;
    PhysicsEntity(PhysicsEntity&&) = delete;
    PhysicsEntity& operator=(PhysicsEntity&&) = delete;

    void update(const tile::TileMap& tile_map, const Vector2& movement, const float& deltaTime);

    void render(Texture2D texture) const;

    [[nodiscard]]
    Vector2 velocity() const
    {
        return velocity_;
    }

    [[nodiscard]]
    Rectangle box() const
    {
        return box_;
    }

    void setVelocity(Vector2 velocity_change)
    {
        velocity_.x += velocity_change.x;
        velocity_.y += velocity_change.y;
    }

private:
    const std::string type_;
    Rectangle box_ { 0.0, 0.0, 0.0, 0.0 };
    Vector2 velocity_ { 0.0, 0.0 };
    float speed_ { 50.0 };
};

}  // namespace physics
