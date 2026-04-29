#pragma once

#include <Camera.h>
#include <Entities.h>
#include <TileMap.h>
#include <raylib.h>

#include <unordered_map>
#include <vector>

class Game
{
public:
    Game();

    void run();

    void update();

    void render();

private:
    static constexpr int screen_width { 600 };
    static constexpr int screen_height { 480 };
    static constexpr int target_fps { 60 };
    float dt_ { 0.0 };

    raylib_ex::Camera2DEx camera_;

    physics::PhysicsEntity player_;

    tile::TileMap tile_map_;

    std::unordered_map<std::string, std::vector<Texture2D>> textures_;
};
