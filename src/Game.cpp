#include <Game.h>
#include <Utils.h>

#include <string>

Game::Game()
    : camera_({ (float)screen_width / 2, (float)screen_height / 2 },
              { (float)screen_width / 4, (float)screen_height / 4 },
              0.0,
              2.0),
      player_("player", (Rectangle) { .x = 50.0, .y = 50.0, .width = 8.0, .height = 15.0 })
{
    InitWindow(screen_width, screen_height, "Ninja Game");
    SetTargetFPS(target_fps);

    const std::string image_path { "../assets/images/" };
    textures_["background"] = { loadTextureKey(image_path + "background.png", BLANK) };
    textures_["player"] = { loadTextureKey(image_path + "entities/player.png", BLACK) };
    textures_["grass"] = loadTextureKeyFolder(image_path + "tiles/grass", BLANK);
    textures_["stone"] = loadTextureKeyFolder(image_path + "tiles/stone", BLANK);

    camera_.setCameraMode(raylib_ex::Camera2DExMode::FOLLOW);
}

void Game::update()
{
    Vector2 movement { 0, 0 };
    if (IsKeyDown(KEY_A)) {
        movement.x = -1;
    }
    if (IsKeyDown(KEY_D)) {
        movement.x = 1;
    }
    if (IsKeyPressed(KEY_SPACE)) {
        player_.setVelocity({ 0.0, -3 });
    }
    player_.update(tile_map_, movement, dt_);

    camera_.update(player_, tile_map_, dt_, screen_width, screen_height);
}

void Game::render()
{
    BeginDrawing();

    // ClearBackground(RAYWHITE);
    DrawTextureEx(textures_["background"][0], { 0.0, 0.0 }, 0.0, camera_.raw().zoom, WHITE);

    DrawFPS(10, 10);

    BeginMode2D(camera_.raw());
    {
        tile_map_.render(textures_);
        player_.render(textures_["player"][0]);
    }
    EndMode2D();

    EndDrawing();
}

void Game::run()
{
    while (!WindowShouldClose()) {
        dt_ = GetFrameTime();

        update();
        render();

        if (IsKeyPressed(KEY_ESCAPE)) {
            break;
        }
    }

    CloseWindow();
}
