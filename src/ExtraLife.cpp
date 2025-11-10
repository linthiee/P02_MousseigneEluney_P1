#include "ExtraLife.h"
#include "globals.h"

ExtraLife::ExtraLife(Vector2 pos, int texID, float width, float height) : Collectible(pos, texID, width, height) 
{
	position = pos;
	textureID = texID;
	this->width = width;
	this->height = height;

	timer = 10.0f;
}

void ExtraLife::WasCollected(Player* player)
{
	if (player->GetLife() < 3)
	{
		player->UpdateLife(1);
	}
}

void ExtraLife::Update()
{
	timer -= deltaT;

	if (timer <= 0.0f)
	{
		DeleteEntity();
	}
}

void ExtraLife::Draw()
{
	DrawRectangleGradientV(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(width), static_cast<int>(height), LIME, WHITE);
}
