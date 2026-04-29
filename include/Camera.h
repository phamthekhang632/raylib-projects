#include <Entities.h>
#include <TileMap.h>
#include <raylib.h>

#include <cstdint>

namespace raylib_ex
{

enum Camera2DExMode : uint8_t {
    CENTER = 0,
    FOLLOW_X,
    FOLLOW_Y,
    FOLLOW
};

class Camera2DEx
{
public:
    Camera2DEx(const Vector2& offset,
               const Vector2& target,
               const float& rotation,
               const float& zoom);
    ~Camera2DEx() = default;

    Camera2DEx(const Camera2DEx&) = delete;
    Camera2DEx& operator=(const Camera2DEx&) = delete;
    Camera2DEx(Camera2DEx&&) = delete;
    Camera2DEx& operator=(Camera2DEx&&) = delete;

    void update(const physics::PhysicsEntity& player,
                const environment::TileMap& tile_map,
                const float& delta,
                const int& screen_width,
                const int& screen_height);

    [[nodiscard]]
    Camera2D raw()
    {
        return raw_;
    }

    void setCameraMode(const Camera2DExMode& mode) { mode_ = mode; }

private:
    Camera2D raw_;
    Camera2DExMode mode_ { CENTER };
};

}  // namespace raylib_ex
