#include "ExtraLife.h"

ExtraLife::ExtraLife(Vector2 pos, int texID, float width, float height) : Collectible(pos, texID, width, height) 
{
	position = pos;
	textureID = texID;
	this->width = width;
	this->height = height;
}

void ExtraLife::WasCollected(Player* player)
{
	player->UpdateLife(1);
}

void ExtraLife::Update()
{

}

void ExtraLife::Draw()
{
	DrawRectangleGradientV(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(width), static_cast<int>(height), LIME, WHITE);
}
