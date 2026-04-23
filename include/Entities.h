#pragma once

#include <raylib.h>

#include <string>

class PhysicsEntity
{
public:
    PhysicsEntity(std::string type, Vector2 position, Vector2 size)
        : type_(std::move(type)), position_(position), size_(size) { };

    ~PhysicsEntity() = default;

    PhysicsEntity(const PhysicsEntity&) = delete;
    PhysicsEntity& operator=(const PhysicsEntity&) = delete;
    PhysicsEntity(PhysicsEntity&&) = delete;
    PhysicsEntity& operator=(PhysicsEntity&&) = delete;

    void update(Vector2 movement, float deltaTime);

    void render(Texture2D texture);

    [[nodiscard]]
    Vector2 getPosition() const
    {
        return position_;
    }

    [[nodiscard]]
    Vector2 getVelocity() const
    {
        return velocity_;
    }

private:
    const std::string type_;
    Vector2 position_;
    Vector2 velocity_ { 0.0, 0.0 };
    float speed_ { 100.0 };
    Vector2 size_;
};
