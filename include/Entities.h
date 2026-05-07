#pragma once

#include <TileMap.h>
#include <Utils.h>
#include <raylib.h>

#include <memory>
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

    void update(const environment::TileMap& tile_map,
                const Vector2& movement,
                const float& deltaTime);

    void render() const;

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

    void setAction(const std::string& action)
    {
        if (action != action_) {
            action_ = action;

            std::string key = type_ + "/" + action_;

            auto it = animations->find(key);
            if (it != animations->end()) {
                animation_ = std::make_unique<Animation>(it->second);
            }
        }
    }

    static std::unique_ptr<std::unordered_map<std::string, std::vector<Texture2D>>> textures;
    static std::unique_ptr<std::unordered_map<std::string, Animation>> animations;

    const Rectangle& box() { return box_; }
    const std::unordered_map<std::string, bool>& collisions() const { return collisions_; }

    const Animation* animation() const { return animation_.get(); }
    const Vector2& animationOffset() const { return animation_offset_; }
    const bool& faceLeft() const { return face_left_; }

private:
    const std::string type_;
    Rectangle box_ { 0.0, 0.0, 0.0, 0.0 };
    Vector2 velocity_ { 0.0, 0.0 };
    float speed_ { 50.0 };
    std::unordered_map<std::string, bool> collisions_ {
        {    "up", false },
        {  "down", false },
        {  "left", false },
        { "right", false }
    };

    std::unique_ptr<Animation> animation_;
    std::string action_;
    Vector2 animation_offset_ { -3, -3 };
    bool face_left_ { false };
};

class Player : public PhysicsEntity
{
public:
    Player() = default;

    Player(Rectangle box);

    ~Player() = default;

    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    Player(const Player&&) = delete;
    Player& operator=(const Player&&) = delete;

    void update(const environment::TileMap& tile_map,
                const Vector2& movement,
                const float& deltaTime);

    void render();

private:
    uint64_t air_time_ { 0 };
};

}  // namespace physics
