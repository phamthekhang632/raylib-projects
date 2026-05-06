#include <Cloud.h>
#include <Utils.h>
#include <raylib.h>

#include <iostream>
#include <random>

namespace environment
{

std::uniform_real_distribution<float> Cloud::position_x_dist(0, 600);
std::uniform_real_distribution<float> Cloud::position_y_dist(0, 480);
std::uniform_real_distribution<float> Cloud::speed_dist(0.05F, 0.1F);
std::uniform_real_distribution<float> Cloud::depth_dist(0.6F, 0.8F);
std::uniform_int_distribution<size_t> Cloud::texture_dist(0, 1);

Cloud::Cloud(Vector2 position, float speed, float depth, const Texture2D* texture)
    : position_(position), speed_(speed), depth_(depth), texture_(texture)
{
}

std::pair<float, std::unique_ptr<Cloud>> Cloud::generate(std::mt19937& gen,
                                                         const std::vector<Texture2D>& textures)
{
    float d = depth_dist(gen);
    float x = position_x_dist(gen);
    float y = position_y_dist(gen);
    float s = speed_dist(gen);
    const auto* tex = &textures[texture_dist(gen)];

    return { d, std::make_unique<Cloud>(Vector2 { x, y }, s, d, tex) };
}

std::multimap<float, std::unique_ptr<Cloud>>
Cloud::generateBatch(std::mt19937& gen, const std::vector<Texture2D>& textures, uint8_t count)
{
    std::multimap<float, std::unique_ptr<Cloud>> clouds;

    for (int i = 0; i < count; i++) {
        Vector2 position = { position_x_dist(gen), position_y_dist(gen) };
        float speed = speed_dist(gen);
        float depth = depth_dist(gen);

        clouds.emplace(
            depth,
            std::make_unique<Cloud>(position, speed, depth, &textures[texture_dist(gen)]));
    }
    return clouds;
}

void Cloud::update()
{
    position_.x += speed_;
}

void Cloud::render(const Vector2& offset)
{
    Coordinate render_pos = { position_.x - (offset.x * depth_),
                              position_.y - (offset.y * depth_) };

    DrawTexture(*texture_,
                static_cast<int>(render_pos.first),
                static_cast<int>(render_pos.second),
                WHITE);
};

}  // namespace environment
