#include <TileMap.h>
#include <raylib.h>

#include <cstdint>
#include <memory>
#include <random>
#include <vector>

namespace environment
{

class Cloud
{
public:
    Cloud(Vector2 position, float speed, float depth, const Texture2D* texture);
    ~Cloud() = default;

    Cloud(const Cloud&) = delete;
    Cloud& operator=(const Cloud&) = delete;
    Cloud(const Cloud&&) = delete;
    Cloud& operator=(const Cloud&&) = delete;

    static std::pair<float, std::unique_ptr<Cloud>> generate(
        std::mt19937& gen,
        const std::vector<Texture2D>& textures);

    static std::multimap<float, std::unique_ptr<Cloud>>
    generateBatch(std::mt19937& gen, const std::vector<Texture2D>& textures, uint8_t count = 16);

    void update();

    void render(const Vector2& offset);

    Vector2 position() { return position_; }

    static void setPositionXDist(float start, float end)
    {
        position_x_dist = std::uniform_real_distribution<float>(start, end);
    }

    static void setPositionYDist(float start, float end)
    {
        position_y_dist = std::uniform_real_distribution<float>(start, end);
    }

private:
    static std::uniform_real_distribution<float> position_x_dist;
    static std::uniform_real_distribution<float> position_y_dist;
    static std::uniform_real_distribution<float> speed_dist;
    static std::uniform_real_distribution<float> depth_dist;
    static std::uniform_int_distribution<size_t> texture_dist;

    Vector2 position_;
    float speed_;
    float depth_;

    const Texture2D* texture_;
};

}  // namespace environment
