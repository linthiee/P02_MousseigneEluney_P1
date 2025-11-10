#include "globals.h"
#include "entity.h"
#include "player.h"
#include "enemy.h"
#include "powerupManager.h"
#include "collectible.h"
#include "stateManager.h"

#include "raylib.h"

#include <vector>
#include <iostream>
#include <ctime>

static void UpdateDeltaTime();
static void InitializeEnemyQuant(std::vector<Entity*>& entities, Player* player);
static bool CollisionRectangles(Entity* a, Entity* b);

int main()
{
	Player* player = new Player({ static_cast<float>(screenWidth / 2),  static_cast<float>(screenHeight / 2) }, 0, 50.0f, 50.0f);
	std::vector<Entity*> entities = {};
	entities.push_back(player);

	PowerUpManager powerUpManager(10.0f);
	StateManager stateManager(player);

	player->SetStateManager(&stateManager);

	SetRandomSeed(static_cast<unsigned int>(time(nullptr)));

	InitializeEnemyQuant(entities, player);

	InitWindow(screenWidth, screenHeight, "Parcial 02 Programacion 01");

	while (!WindowShouldClose())
	{
		UpdateDeltaTime();

		if (!stateManager.IsGameOver())
		{
			stateManager.Update();

			for (int i = 0; i < entities.size(); i++)
			{
				entities[i]->Update();
			}

			for (int i = 0; i < entities.size(); i++)
			{
				for (int j = i + 1; j < entities.size(); j++)
				{
					Entity* a = entities[i];
					Entity* b = entities[j];

					if (CollisionRectangles(a, b))
					{
						a->IsCollidingWith(b);
						b->IsCollidingWith(a);
					}
				}
			}

			int activePowerUps = 0;
			for (int i = static_cast<int>(entities.size()) - 1; i >= 0; i--)
			{
				if (entities[i]->IsEntityDeleted())
				{
					delete entities[i];
					entities.erase(entities.begin() + i);
				}
				else
				{
					if (dynamic_cast<Collectible*>(entities[i]) != nullptr)
					{
						activePowerUps++;
					}
				}
			}

			powerUpManager.Update(deltaT, entities, activePowerUps);
		}

		BeginDrawing();

		ClearBackground(GRAY);

		for (int i = 0; i < entities.size(); i++)
		{
			entities[i]->Draw();
		}

		stateManager.Draw();

		if (stateManager.IsGameOver())
		{
			Color color;

			color.a = 125;
			color.r = 0;
			color.g = 0;
			color.b = 0;

			DrawRectangle(0, 0, screenWidth, screenHeight, color);

			DrawText("GAME OVER", screenWidth / 2 - 100, 20, 40, RED);

			if (hasWon)
			{
				DrawText("YOU WON!", screenWidth / 2 - 80, 100, 30, GREEN);
			}
			else
			{
				DrawText("YOU LOSE!", screenWidth / 2 - 80, 100, 30, RED);
			}

			DrawText(TextFormat("Final Score: %i", static_cast<int>(stateManager.GetScore())), screenWidth / 2 - 100, 160, 20, WHITE);
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

void InitializeEnemyQuant(std::vector<Entity*>& entities, Player* player)
{
	int enemyQuant = GetRandomValue(2, 3);

	for (int i = 0; i < enemyQuant; i++)
	{
		Enemy* enemy = new Enemy({ 0.0f, 0.0f }, 0, 50.0f, 50.0f, player);
		entities.push_back(enemy);
	}
}

static bool CollisionRectangles(Entity* a, Entity* b)
{
	return (a->GetPosition().x < b->GetPosition().x + b->GetWidth() &&
		a->GetPosition().x + a->GetWidth() > b->GetPosition().x &&
		a->GetPosition().y < b->GetPosition().y + b->GetHeight() &&
		a->GetPosition().y + a->GetHeight() > b->GetPosition().y);
}