#pragma once

#include <raylib.h>

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

template <typename... Args>
inline void logInfo(Args... args)
{
    ((std::cout << args << " "), ...) << std::endl;
}

inline Texture2D loadTextureKey(const std::string& path, const Color& color_key)
{
    Image image = LoadImage(path.c_str());
    ImageColorReplace(&image, color_key, BLANK);
    return LoadTextureFromImage(image);
}

inline std::vector<Texture2D> loadTextureKeyFolder(const std::string& folder_path,
                                                   const Color& color_key)
{
    std::vector<fs::path> paths;
    for (const fs::directory_entry& entry : fs::directory_iterator(folder_path)) {
        if (entry.is_regular_file()) {
            paths.emplace_back(entry.path());
        }
    }
    std::ranges::sort(paths.begin(), paths.end());

    std::vector<Texture2D> textures;
    textures.reserve(paths.size());
    for (auto& path : paths) {
        textures.emplace_back(loadTextureKey(path, color_key));
    }

    return textures;
}
