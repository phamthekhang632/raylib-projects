#include <Game.h>

#include <string>

#define PATH "../assets/images/"

Game::Game()
{
    InitWindow(screenWidth, screenHeight, "Ninja Game");
    textures_["player"] = LoadTexture(PATH "entities/player.png");
    SetTargetFPS(targetFPS);
}

void Game::update(double deltaTime)
{
    Vector2 movement { 0, 0 };
    if (IsKeyDown(KEY_A)) {
        movement.x = -1;
    }
    if (IsKeyDown(KEY_D)) {
        movement.x = 1;
    }
    player_.update(movement, deltaTime);
}

void Game::render()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);
    DrawFPS(10, 10);
    player_.render(textures_["player"]);

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
