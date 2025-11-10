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

	SetRandomSeed(static_cast<unsigned int>(time(nullptr)));

	InitializeEnemyQuant(entities, player);

	InitWindow(screenWidth, screenHeight, "Parcial 02 Programacion 01");

	while (!WindowShouldClose())
	{
		UpdateDeltaTime();

		if (stateManager.IsGameOver())
		{
			break;
		}

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

		BeginDrawing();

		ClearBackground(GRAY);

		for (int i = 0; i < entities.size(); i++)
		{
			entities[i]->Draw();
		}

		stateManager.Draw();

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
	int enemyQuant = GetRandomValue(1, 3);

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