#include "raylib.h"
#include <stdio.h>

struct RainObject {
  Vector2 position;
  float speed;
  double createdAt;
  bool active;
};
struct RainObject createInitialRainObject(int minWidth, int maxWidth,
                                          int minHeight, int maxHeight,
                                          float speed, bool active) {
  struct RainObject output = {
      .position = {(float)GetRandomValue(minWidth, maxWidth),
                   (float)GetRandomValue(minHeight, maxHeight)},
      .speed = speed,
      .createdAt = GetTime(),
      .active = active};
  return output;
};

int main() {
  // Initialization
  // -------------
  const int screenWidth = 800;
  const int screenHeight = 450;
  InitWindow(screenWidth, screenHeight, "Moving circle!");

  const Vector2 floorPosition = {0,
                                 (float)screenHeight - (float)screenHeight / 3};
  const Vector2 floorSize = {screenWidth, (float)screenHeight / 3};
  Vector2 playerSize = {20, 20};
  Vector2 playerPosition = {(float)screenWidth / 2.0,
                            floorPosition.y - (float)playerSize.y};
  int playerScore = 0;
  char playerScoreString[5];
  SetTargetFPS(60);

  const Vector2 spawnZone = {screenWidth, 0};

  struct RainObject rainObjects[10] = {
      createInitialRainObject(0, spawnZone.x, 0, spawnZone.y,
                              GetRandomValue(20, 40), false),
      createInitialRainObject(0, spawnZone.x, 0, spawnZone.y,
                              GetRandomValue(20, 40), false),
      createInitialRainObject(0, spawnZone.x, 0, spawnZone.y,
                              GetRandomValue(20, 40), false),
      createInitialRainObject(0, spawnZone.x, 0, spawnZone.y,
                              GetRandomValue(20, 40), false),
      createInitialRainObject(0, spawnZone.x, 0, spawnZone.y,
                              GetRandomValue(20, 40), false),
      createInitialRainObject(0, spawnZone.x, 0, spawnZone.y,
                              GetRandomValue(20, 40), false),
      createInitialRainObject(0, spawnZone.x, 0, spawnZone.y,
                              GetRandomValue(20, 40), false),
      createInitialRainObject(0, spawnZone.x, 0, spawnZone.y,
                              GetRandomValue(20, 40), false),
      createInitialRainObject(0, spawnZone.x, 0, spawnZone.y,
                              GetRandomValue(20, 40), false),
      createInitialRainObject(0, spawnZone.x, 0, spawnZone.y,
                              GetRandomValue(20, 40), false)};

  int rainObjectsLength = sizeof(rainObjects) / sizeof(rainObjects[0]);

  while (!WindowShouldClose()) {
    float deltaTime = GetFrameTime();
    double timeSinceWitdownInit = GetTime();
    if (IsKeyDown(KEY_RIGHT))
      playerPosition.x += 2.0;
    if (IsKeyDown(KEY_LEFT))
      playerPosition.x -= 2.0;
    if (IsKeyDown(KEY_UP))
      playerPosition.y -= 2.0;
    if (IsKeyDown(KEY_DOWN))
      playerPosition.y += 2.0;
    BeginDrawing();
    {
      ClearBackground(RAYWHITE);

      // Draw floor
      DrawRectangleV(floorPosition, floorSize, GRAY);
      // Draw player
      DrawRectangleV(playerPosition, playerSize, BLUE);
      for (int i = 0; i < rainObjectsLength; i++) {

        if (rainObjects[i].active) {
          rainObjects[i].position.y += rainObjects[i].speed * deltaTime;
          DrawCircleV(rainObjects[i].position, 5, RED);
        } else {
          if (GetRandomValue(0, 100000) % 100 == 0) {
            rainObjects[i] = createInitialRainObject(
                0, screenWidth, 0, screenHeight / 8, GetRandomValue(20, 40), 1);
          }
        }

        if (rainObjects[i].position.y > playerPosition.y &&
            rainObjects[i].position.y < playerPosition.y + playerSize.y &&
            rainObjects[i].position.x > playerPosition.x &&
            rainObjects[i].position.x < playerPosition.x + playerSize.x && rainObjects[i].active) {
          rainObjects[i].active = false;
		  playerScore += 1;
        }

        if (rainObjects[i].position.y > floorPosition.y) {
          rainObjects[i].active = false;
        }
      }
    }
	DrawLine(0, playerPosition.y + playerSize.y, screenWidth, playerPosition.y + playerSize.y, BLUE);
	DrawLine(0, playerPosition.y , screenWidth, playerPosition.y , BLUE);

	DrawLine(playerPosition.x + playerSize.x, 0, playerPosition.x + playerSize.x, screenHeight, BLUE);
	DrawLine(playerPosition.x, 0, playerPosition.x , screenHeight, BLUE);
	DrawText(TextFormat("Score: %d", playerScore), 10, 10, 10, GREEN);
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
