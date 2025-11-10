#include "ScoreMultiplyer.h"
#include "StateManager.h"
#include "globals.h"

ScoreMultiplyer::ScoreMultiplyer(Vector2 pos, int texID, float width, float height) : Collectible(pos, texID, width, height)
{
	position = pos;
	textureID = texID;
	this->width = width;
	this->height = height;
	multiplierValue = 4;

	timer = 10.0f;
}

void ScoreMultiplyer::WasCollected(Player* player)
{
	float buffDuration = 5.0f;

	player->ActivateScoreMultiplier(multiplierValue, buffDuration);
}

void ScoreMultiplyer::Update()
{
	timer -= deltaT;

	if (timer <= 0.0f)
	{
		DeleteEntity();
	}
}

void ScoreMultiplyer::Draw()
{
	DrawRectangleGradientV(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(width), static_cast<int>(height), YELLOW, WHITE);
}
