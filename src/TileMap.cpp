#include <TileMap.h>

#include <iostream>

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
        // std::cout << type.first << "\t" << type.second << "\t" << coor.first << "\t" <<
        // coor.second
        //           << "\n";
        // TODO: check if type is available before drawing
        DrawTexture(textures.at(type.first)[type.second], coor.first, coor.second, WHITE);
    }

    /* Render grid */
    for (const auto& [coor, type] : grid_map_) {
        // std::cout << type.first << "\t" << type.second << "\t" << coor.first << "\t" <<
        // coor.second
        //           << "\n";
        DrawTexture(textures.at(type.first)[type.second],
                    coor.first * tile_size_,
                    coor.second * tile_size_,
                    WHITE);
    }
}
