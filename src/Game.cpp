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
      player_("player", (Rectangle) { .x = 50.0, .y = 50.0, .width = 8.0, .height = 15.0 })
{
    InitWindow(screen_width_, screen_height_, "Ninja Game");
    SetTargetFPS(target_fps_);

    const std::string image_path { "../assets/images/" };
    textures_["player"] = { loadTextureKey(image_path + "entities/player.png", BLACK) };
    textures_["grass"] = loadTextureKeyFolder(image_path + "tiles/grass", BLANK);
    textures_["stone"] = loadTextureKeyFolder(image_path + "tiles/stone", BLANK);
    // TOFIX: load texture for grass and stone
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
    tile_map_.render(textures_);
    player_.render(textures_["player"][0]);

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
