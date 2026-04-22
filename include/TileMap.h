#pragma once

#include <raylib.h>

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

class TileMap
{
public:
    TileMap(int tile_size = 16);

    void render(const std::unordered_map<std::string, std::vector<Texture2D>>& textures);

private:
    int tile_size_;
    std::map<std::pair<int, int>, std::pair<std::string, uint>> grid_map_;
    std::map<std::pair<int, int>, std::pair<std::string, uint>> background_map_;
};
