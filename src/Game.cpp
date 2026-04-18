#include <Game.h>
#include <Utils.h>

#include <string>

Game::Game()
    : camera_({
          .offset = { (float)screen_width_ / 2, (float)screen_height_ / 2 },
          .target = { (float)screen_width_ / 4, (float)screen_height_ / 4 },
          .rotation = 0.0,
          .zoom = 2.0
}),
      player_("player", { 50.0, 50.0 }, { 8.0, 15.0 })
{
    InitWindow(screen_width_, screen_height_, "Ninja Game");
    SetTargetFPS(target_fps_);

    const std::string path { "../assets/images/" };
    textures_["player"] = loadTextureKey(path + "entities/player.png", BLACK);
}

void Game::update(float deltaTime)
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

    ClearBackground(Color { 14, 219, 248 });
    DrawFPS(10, 10);
    BeginMode2D(camera_);
    player_.render(textures_["player"]);

    EndDrawing();
}

void Game::run()
{
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        update(dt);
        render();

        if (IsKeyPressed(KEY_ESCAPE)) {
            break;
        }
    }

    CloseWindow();
}
