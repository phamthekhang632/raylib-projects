#pragma once

#include <raylib.h>

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

namespace environment
{

using Coordinate = std::pair<int, int>;

struct CoordinateHash {
    size_t operator()(const std::pair<int, int>& v) const
    {
        return std::hash<int> {}(v.first) ^ (std::hash<int> {}(v.second) << 1);
    }
};

class TileMap
{
public:
    TileMap(int tile_size = 16);

    void render(const std::unordered_map<std::string, std::vector<Texture2D>>& textures,
                const Vector2& top_left,
                const Vector2& bottom_right);

    Coordinate convertWorld2Tile(float x, float y) const;

    std::vector<Coordinate> tilesArround(float x, float y) const;

    std::vector<Rectangle> physicsTilesArround(float x, float y) const;

private:
    int tile_size_;
    std::unordered_map<Coordinate, std::pair<std::string, uint>, CoordinateHash> grid_map_;
    std::unordered_map<Coordinate, std::pair<std::string, uint>, CoordinateHash> background_map_;
};

}  // namespace environment
