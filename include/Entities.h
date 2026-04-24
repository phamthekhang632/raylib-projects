#pragma once

#include <raylib.h>

#include <string>

class PhysicsEntity
{
public:
    PhysicsEntity(std::string type, Rectangle box) : type_(std::move(type)), box_(box) { };
    ~PhysicsEntity() = default;

    PhysicsEntity(const PhysicsEntity&) = delete;
    PhysicsEntity& operator=(const PhysicsEntity&) = delete;
    PhysicsEntity(PhysicsEntity&&) = delete;
    PhysicsEntity& operator=(PhysicsEntity&&) = delete;

    void update(Vector2 movement, float deltaTime);

    void render(Texture2D texture) const;

    [[nodiscard]]
    Vector2 getVelocity() const
    {
        return velocity_;
    }

private:
    const std::string type_;
    Rectangle box_;
    Vector2 velocity_ { 0.0, 0.0 };
    float speed_ { 100.0 };
};
