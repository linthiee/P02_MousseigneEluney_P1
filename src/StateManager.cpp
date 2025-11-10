#include "StateManager.h"
#include "globals.h"
#include "player.h"

StateManager::StateManager(Player* player)
{
	this->player = player;
	score = 0.0f;
	isGameOver = false;
	timer = 60.0f;
	multiplier = 1;
	multiplierTimer = 0.0f;
}

void StateManager::Update()
{
	timer -= deltaT;
	score += deltaT * multiplier;

	if (multiplierTimer > 0.0f)
	{
		multiplierTimer -= deltaT;

		if (multiplierTimer <= 0.0f)
		{
			multiplier = 1;
		}
	}
}

void StateManager::Draw()
{
	int startX = 10;
	int rectWidth = 20;
	int rectHeight = 20;
	int spacing = 4;

	DrawText(TextFormat("Score: %i", static_cast<int>(score)), 10, 30, 20, WHITE);

	for (int i = 0; i < player->GetLife(); i++)
	{
		int xPos = startX + (i * (rectWidth + spacing));
		DrawRectangle(xPos, 5, rectWidth, rectHeight, BLUE);
	}
	DrawText(TextFormat("Time: %.2f", timer), 650, 10, 20, WHITE);
}

void StateManager::SetMultiplier(int mult, float duration)
{
	multiplier = mult;
	multiplierTimer = duration;
}

float StateManager::GetScore()
{
	return score;
}

bool StateManager::IsGameOver()
{
	return isGameOver;
}

void StateManager::AddScore(int points)
{
	score += points;
}

void StateManager::CheckGameOver()
{
	if (player->GetLife() <= 0)
	{
		isGameOver = true;
	}
	else if (timer <= 0.0f)
	{
		isGameOver = true;
	}
}
