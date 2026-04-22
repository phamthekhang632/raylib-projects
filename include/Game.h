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
    const int screen_width_ = 600;
    const int screen_height_ = 480;
    const int target_fps_ = 60;

    Camera2D camera_;

    PhysicsEntity player_;

    TileMap tile_map_;

    std::unordered_map<std::string, std::vector<Texture2D>> textures_;
};
