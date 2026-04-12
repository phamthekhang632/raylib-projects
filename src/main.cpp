#include "raylib.h"

struct Game {
    Game();

    void run();

    void update(double deltaTime);

    void render();

  private:
    static constexpr int screenWidth = 800;
    static constexpr int screenHeight = 450;
    static constexpr int targetFPS = 60;

    Texture2D ninjaTexture_ {};
    Vector2 ninjaPosition_ { 100, 100 };
    double ninjaSpeed_ { 50.0 };
};

Game::Game()
{
    InitWindow(screenWidth, screenHeight, "Ninja Game");
    ninjaTexture_ = LoadTexture("assets/images/entities/player/idle/00.png");
    SetTargetFPS(targetFPS);
}

void Game::update(double deltaTime)
{
    if (IsKeyDown(KEY_W)) {
        ninjaPosition_.y -= ninjaSpeed_ * deltaTime;
    }
    if (IsKeyDown(KEY_A)) {
        ninjaPosition_.x -= ninjaSpeed_ * deltaTime;
    }
    if (IsKeyDown(KEY_S)) {
        ninjaPosition_.y += ninjaSpeed_ * deltaTime;
    }
    if (IsKeyDown(KEY_D)) {
        ninjaPosition_.x += ninjaSpeed_ * deltaTime;
    }
}

void Game::render()
{
    BeginDrawing();
    {
        ClearBackground(RAYWHITE);
        DrawTextureEx(ninjaTexture_, ninjaPosition_, 0.0f, 2.0f, WHITE);
        DrawFPS(10, 10);
    }
    EndDrawing();
}

void Game::run()
{
    while (!WindowShouldClose()) {
        double deltaTime = GetFrameTime();

        update(deltaTime);
        render();

        if (IsKeyPressed(KEY_ESCAPE)) {
            break;
        }
    }

    CloseWindow();
}

int main()
{
    Game game;
    game.run();
    return 0;
}
