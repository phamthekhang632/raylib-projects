#pragma once

#include <Camera.h>
#include <Cloud.h>
#include <Entities.h>
#include <TileMap.h>
#include <raylib.h>

#include <random>
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

    std::unordered_map<std::string, std::vector<Texture2D>> textures_;
    std::unordered_map<std::string, Animation> animations_;

    raylib_ex::Camera2DEx camera_;

    physics::Player player_;

    environment::TileMap tile_map_;
    std::multimap<float, std::unique_ptr<environment::Cloud>> clouds_;
    const int cloud_count_ = 24;

    // std::random_device rd;
    std::mt19937 gen_;
};
