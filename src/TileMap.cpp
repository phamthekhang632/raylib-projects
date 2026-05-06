#include <TileMap.h>

#include <cmath>
#include <iostream>
#include <ranges>
#include <set>

namespace environment
{

// clang-format off
const std::vector<Coordinate> neighbors_offset = {
    { -1, -1 },    {  0, -1 },    {  1, -1 },
    { -1,  0 },    {  0,  0 },    {  1,  0 },
    { -1,  1 },    {  0,  1 },    {  1,  1 },
};
// clang-format on

const std::set<std::string> physics_tiles { "grass", "stone" };

TileMap::TileMap(int tile_size) : tile_size_(tile_size)
{
    for (int i = 0; i < 10; ++i) {
        grid_map_[{ 3 + i, 10 }] = { "grass", 1 };
        grid_map_[{ 10, 3 + i }] = { "stone", 1 };
    }
}

void TileMap::render(const std::unordered_map<std::string, std::vector<Texture2D>>& textures,
                     const Vector2& top_left,
                     const Vector2& bottom_right)
{
    /* Render background */
    auto x_background = std::views::iota(static_cast<int>(top_left.x),
                                         static_cast<int>(bottom_right.x));
    auto y_background = std::views::iota(static_cast<int>(top_left.y),
                                         static_cast<int>(bottom_right.y));
    for (const auto& x : x_background) {
        for (const auto& y : y_background) {
            if (background_map_.contains(Coordinate(x, y))) {
                const auto& type = background_map_.at({ x, y });
                DrawTexture(textures.at(type.first)[type.second], x, y, WHITE);
            }
        }
    }

    /* Render grid */
    auto x_grid = std::views::iota(
        static_cast<int>(std::floor(top_left.x / static_cast<float>(tile_size_))),
        static_cast<int>(std::ceil(bottom_right.x / static_cast<float>(tile_size_))));
    auto y_grid = std::views::iota(
        static_cast<int>(std::floor(top_left.y / static_cast<float>(tile_size_))),
        static_cast<int>(std::ceil(bottom_right.y / static_cast<float>(tile_size_))));
    for (const auto& x : x_grid) {
        for (const auto& y : y_grid) {
            if (grid_map_.contains(Coordinate(x, y))) {
                const auto& type = grid_map_.at({ x, y });
                DrawTexture(textures.at(type.first)[type.second],
                            x * tile_size_,
                            y * tile_size_,
                            WHITE);
            }
        }
    }
}

Coordinate TileMap::convertWorld2Tile(float x, float y) const
{
    return { std::round(x / static_cast<float>(tile_size_)),
             std::round(y / static_cast<float>(tile_size_)) };
}

// UNSTABLE
std::vector<Coordinate> TileMap::tilesArround(float x, float y) const
{
    Coordinate tile_coord = convertWorld2Tile(x, y);
    std::vector<Coordinate> tiles_arround;
    for (Coordinate offset : neighbors_offset) {
        offset.first += tile_coord.first;
        offset.second += tile_coord.second;
        if (grid_map_.contains(offset)) {
            tiles_arround.emplace_back(offset);
        }
    }
    return tiles_arround;
}

std::vector<Rectangle> TileMap::physicsTilesArround(float x, float y) const
{
    Coordinate tile_coord = convertWorld2Tile(x, y);
    std::vector<Coordinate> neighbors_coord;
    for (Coordinate offset : neighbors_offset) {
        offset.first += tile_coord.first;
        offset.second += tile_coord.second;
        if (grid_map_.contains(offset)) {
            neighbors_coord.emplace_back(offset);
        }
    }

    std::vector<Rectangle> tiles_arround;
    for (auto& coord : neighbors_coord) {
        if (physics_tiles.contains(grid_map_.at(coord).first)) {
            tiles_arround.emplace_back((Rectangle) { static_cast<float>(coord.first * tile_size_),
                                                     static_cast<float>(coord.second * tile_size_),
                                                     static_cast<float>(tile_size_),
                                                     static_cast<float>(tile_size_) });
        }
    }
    return tiles_arround;
}

}  // namespace environment
