#include <Utils.h>

#include <algorithm>
#include <cassert>
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

template <typename... Args>
void logInfo(Args... args)
{
    ((std::cout << args << " "), ...) << std::endl;
}

Texture2D loadTextureKey(const std::string& path, const Color& color_key, bool flip_x, bool flip_y)
{
    Image image = LoadImage(path.c_str());
    ImageFormat(&image, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
    ImageColorReplace(&image, color_key, BLANK);
    if (flip_x) {
        ImageFlipHorizontal(&image);
    }
    if (flip_y) {
        ImageFlipVertical(&image);
    }
    return LoadTextureFromImage(image);
}

std::vector<Texture2D> loadTextureKeyFolder(const std::string& folder_path,
                                            const Color& color_key,
                                            bool flip_x,
                                            bool flip_y)
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
        textures.emplace_back(loadTextureKey(path, color_key, flip_x, flip_y));
    }

    return textures;
}

Animation::Animation(const std::vector<Texture2D>* sprites,
                     const std::vector<Texture2D>* sprites_flipped,
                     uint8_t img_duration,
                     bool loop)
    : sprites_(sprites), sprites_flipped_(sprites_flipped), img_duration_(img_duration), loop_(loop)
{
    assert(sprites_ != nullptr && "Animation created with null sprite pointer!");
};

void Animation::update()
{
    if (loop_) {
        frame_ = (frame_ + 1) % (img_duration_ * sprites_->size());
        return;
    }

    frame_ = std::min<uint8_t>(frame_ + 1, (img_duration_ * sprites_->size()) - 1);
    if (frame_ >= (img_duration_ * sprites_->size()) - 1) {
        done_ = true;
    }
}

const Texture2D& Animation::currentFrame(bool flipped) const
{
    const std::vector<Texture2D>* active_source = (flipped && (sprites_flipped_ != nullptr))
                                                    ? sprites_flipped_
                                                    : sprites_;

    return (*active_source)[frame_ / img_duration_];
}
