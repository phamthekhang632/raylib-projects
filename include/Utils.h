#pragma once

#include <raylib.h>

#include <cmath>
#include <cstdint>
#include <string>
#include <vector>

template <typename... Args>
void logInfo(Args... args);

Texture2D loadTextureKey(const std::string& path,
                         const Color& color_key,
                         bool flip_x = false,
                         bool flip_y = false);

// TODO: shared_ptr
std::vector<Texture2D> loadTextureKeyFolder(const std::string& folder_path,
                                            const Color& color_key,
                                            bool flip_x = false,
                                            bool flip_y = false);

class Animation
{
public:
    Animation(const std::vector<Texture2D>* sprites,
              const std::vector<Texture2D>* sprites_flipped = nullptr,
              uint8_t img_duration = 5,
              bool loop = true);
    ~Animation() = default;

    Animation(const Animation&) = default;
    Animation& operator=(const Animation&) = default;
    Animation(Animation&&) = delete;
    Animation& operator=(Animation&&) = delete;

    void update();

    [[nodiscard]]
    const Texture2D& currentFrame(bool flipped = false) const;

private:
    const std::vector<Texture2D>* sprites_;
    const std::vector<Texture2D>* sprites_flipped_;

    uint64_t frame_ { 0 };
    uint8_t img_duration_ { 5 };
    bool loop_ { true };
    bool done_ { true };
};
