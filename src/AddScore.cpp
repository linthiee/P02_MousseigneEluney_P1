#include "AddScore.h"
#include "StateManager.h"
#include "globals.h"

AddScore::AddScore(Vector2 pos, int texID, float width, float height) : Collectible(pos, texID, width, height)
{
	position = pos;
	textureID = texID;
	this->width = width;
	this->height = height;
	valueToAdd = 20;

	timer = 10.0f;
}

void AddScore::WasCollected(Player* player)
{
	player->ActivateAddScore(valueToAdd);
}

void AddScore::Update()
{
	timer -= deltaT;

	if (timer <= 0.0f)
	{
		DeleteEntity();
	}
}

void AddScore::Draw()
{
	DrawRectangleGradientV(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(width), static_cast<int>(height), MAGENTA, WHITE);
}
