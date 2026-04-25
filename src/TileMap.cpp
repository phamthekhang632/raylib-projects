#include <TileMap.h>

#include <cmath>
#include <iostream>
#include <set>

namespace tile
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

void TileMap::render(const std::unordered_map<std::string, std::vector<Texture2D>>& textures)
{
    /* Render background */
    for (const auto& [coor, type] : background_map_) {
        DrawTexture(textures.at(type.first)[type.second], coor.first, coor.second, WHITE);
    }

    /* Render grid */
    for (const auto& [coor, type] : grid_map_) {
        DrawTexture(textures.at(type.first)[type.second],
                    coor.first * tile_size_,
                    coor.second * tile_size_,
                    WHITE);
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

}  // namespace tile
