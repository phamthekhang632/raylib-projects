#include <Entities.h>
#include <raylib.h>

#include <unordered_map>

class Game
{
public:
    Game();

    void run();

    void update(double deltaTime);

    void render();

private:
    static constexpr int screenWidth = 800;
    static constexpr int screenHeight = 450;
    static constexpr int targetFPS = 60;

    PhysicsEntity player_ {
        "player",
        { 100, 100 },
        {  32,  32 }
    };

    std::unordered_map<std::string, Texture2D> textures_;  // <type, texture>
};
