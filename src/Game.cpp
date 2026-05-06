#include <Game.h>
#include <Utils.h>

#include <string>

Game::Game()
    : camera_({ (float)screen_width / 2, (float)screen_height / 2 },
              { (float)screen_width / 4, (float)screen_height / 4 },
              0.0,
              2.0),
      player_("player", (Rectangle) { .x = 50.0, .y = 50.0, .width = 8.0, .height = 15.0 }),
      gen_(std::random_device {}())
{
    InitWindow(screen_width, screen_height, "Ninja Game");
    SetTargetFPS(target_fps);

    const std::string image_path { "../assets/images/" };
    textures_["background"] = { loadTextureKey(image_path + "background.png", BLACK) };
    textures_["player"] = { loadTextureKey(image_path + "entities/player.png", BLACK) };
    textures_["grass"] = loadTextureKeyFolder(image_path + "tiles/grass", BLACK);
    textures_["stone"] = loadTextureKeyFolder(image_path + "tiles/stone", BLACK);
    textures_["cloud"] = loadTextureKeyFolder(image_path + "clouds", BLACK);

    environment::Cloud::setPositionXDist(0, screen_width);
    environment::Cloud::setPositionYDist(0, screen_height);
    clouds_ = environment::Cloud::generateBatch(gen_, textures_["cloud"], 16);

    camera_.setCameraMode(raylib_ex::Camera2DExMode::FOLLOW);
}

void Game::update()
{
    Vector2 top_left = GetScreenToWorld2D({ 0, 0 }, camera_.raw());
    Vector2 bottom_right = GetScreenToWorld2D({ (float)screen_width, (float)screen_height },
                                              camera_.raw());

    /* Cloud update */
    environment::Cloud::setPositionXDist((2 * top_left.x) - bottom_right.x, top_left.x);
    environment::Cloud::setPositionYDist(top_left.y, bottom_right.y);
    const float margin = 300.0F;
    std::erase_if(clouds_, [&](auto& pair) {
        auto& [depth, cloud] = pair;

        cloud->update();

        Vector2 position = cloud->position();

        bool is_off_screen = (position.x > bottom_right.x + margin
                              || position.x < top_left.x - margin
                              || position.y > bottom_right.y + margin
                              || position.y < top_left.y - margin);

        return is_off_screen;
    });

    if (cloud_count_ > clouds_.size()) {
        auto [d, c] = environment::Cloud::generate(gen_, textures_["cloud"]);
        clouds_.emplace(d, std::move(c));
    }

    /* Player update */
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

    /* Camera update */
    camera_.update(player_, tile_map_, dt_, screen_width, screen_height);
}

void Game::render()
{
    Vector2 top_left = GetScreenToWorld2D({ 0, 0 }, camera_.raw());
    Vector2 bottom_right = GetScreenToWorld2D({ (float)screen_width, (float)screen_height },
                                              camera_.raw());

    BeginDrawing();

    DrawTextureEx(textures_["background"][0], { 0.0, 0.0 }, 0.0, camera_.raw().zoom, WHITE);

    DrawFPS(10, 10);

    BeginMode2D(camera_.raw());
    {
        for (auto& [depth, cloud] : clouds_) {
            cloud->render({ player_.box().x, player_.box().y });
        }

        tile_map_.render(textures_, top_left, bottom_right);
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
