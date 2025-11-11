#include "Collectible.h"

Collectible::Collectible(Vector2 pos, int texID, float width, float height) : Entity(pos, texID, width, height)
{
	position = pos;
	textureID = texID;
	this->width = width;
	this->height = height;
}

void Collectible::WasCollected(Player* player)
{
	player = nullptr;
}

void Collectible::IsCollidingWith(Entity* otherEntity)
{
	otherEntity = nullptr;
}

void Collectible::Update() {}

void Collectible::Draw() {}
