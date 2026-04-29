#pragma once

#include <Entities.h>
#include <raylib.h>
#include <TileMap.h>

#include <unordered_map>
#include <vector>

class Game
{
public:
    Game();

    void run();

    void update(float deltaTime);

    void render();

private:
    static constexpr int screen_width { 600 };
    static constexpr int screen_height { 480 };
    static constexpr int target_fps { 60 };

    Camera2D camera_;

    physics::PhysicsEntity player_;

    tile::TileMap tile_map_;

    std::unordered_map<std::string, std::vector<Texture2D>> textures_;
};
