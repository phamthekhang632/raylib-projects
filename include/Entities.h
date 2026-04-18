// #include <Game.h>

#include <raylib.h>

#include <string>

class PhysicsEntity
{
public:
    PhysicsEntity(std::string type, Vector2 position, Vector2 size);
    ~PhysicsEntity();

    void update(Vector2 movement, double deltaTime);

    void render(Texture2D texture);

    Vector2 getPosition() const { return position_; }

    Vector2 getVelocity() const { return velocity_; }

private:
    std::string type_;
    Vector2 position_;
    Vector2 velocity_ { 0, 0 };
    double speed_ { 100 };
    Vector2 size_;
};
