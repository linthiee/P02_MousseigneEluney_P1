#include "Enemy.h"
#include "raymath.h"
#include "Globals.h"

Enemy::Enemy(Vector2 pos, int texID, float width, float height) : Entity(pos, texID, width, height)
{
	life = 100.0f;
	velocity = { 0.0f, 0.0f };
	speed = 20.0f;

	position = pos;
	textureID = texID;

	this->width = width;
	this->height = height;

	Spawn();
}

void Enemy::Spawn()
{
	int spawnChance = GetRandomValue(1, 100);

	if (spawnChance <= 25)
	{
		position = { static_cast<float>(GetRandomValue(0, 800)), 0.0f };
	}
	else if (spawnChance <= 50)
	{
		position = { static_cast<float>(GetRandomValue(0, 800)), 450.0f };
	}
	else if (spawnChance <= 75)
	{
		position = { 0.0f, static_cast<float>(GetRandomValue(0, 450)) };
	}
	else
	{
		position = { 800.0f, static_cast<float>(GetRandomValue(0, 450)) };
	}
}

void Enemy::Update(Player* player)
{
	Vector2 direction = Vector2Subtract(player->GetPosition(), position);
	velocity = Vector2Normalize(direction);
	position = Vector2Add(position, Vector2Scale(velocity, speed * deltaT));
}

void Enemy::Draw()
{
	DrawRectangleV(position, { width, height }, RED);
}
