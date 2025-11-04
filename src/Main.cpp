#include "globals.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"

#include "raylib.h"

#include <vector>
#include <iostream>
#include <ctime>

static void UpdateDeltaTime();
static void InitializeEnemyQuant(std::vector<Enemy*>& enemies);

int main()
{
	Player* player = new Player({ static_cast<float>(screenWidth / 2),  static_cast<float>(screenHeight / 2) }, 0, 50.0f, 50.0f);
    std::vector<Enemy*> enemies = {};

    SetRandomSeed(static_cast<unsigned int>(time(nullptr)));

    InitializeEnemyQuant(enemies);

    InitWindow(screenWidth, screenHeight, "game");    

    while (!WindowShouldClose())
    {
		UpdateDeltaTime();

		player->Update();
        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i]->Update(player);
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        player->Draw();
        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i]->Draw();
        }

        EndDrawing();
    }

    CloseWindow();     

    return 0;
}

void UpdateDeltaTime()
{
	deltaT = GetFrameTime();
}

void InitializeEnemyQuant(std::vector<Enemy*>& enemies)
{
    int enemyQuant = GetRandomValue(1, 5);

    for (int i = 0; i < enemyQuant; i++)
    {
        Enemy* enemy = new Enemy({ 0.0f, 0.0f }, 0, 50.0f, 50.0f);
        enemies.push_back(enemy);
    }
}