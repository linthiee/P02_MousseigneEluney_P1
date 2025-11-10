#include "Enemy.h"
#include "raymath.h"
#include "Globals.h"

static void CheckOutOfBounds(Vector2& position, float width, float height);

Enemy::Enemy(Vector2 pos, int texID, float width, float height, Player* target) : Entity(pos, texID, width, height)
{
	life = 100.0f;
	velocity = { 0.0f, 0.0f };
	speed = 20.0f;

	position = pos;
	textureID = texID;

	this->target = target;
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

void Enemy::IsCollidingWith(Entity* otherEntity)
{
	Player* player = dynamic_cast<Player*>(otherEntity);

	if (player != nullptr)
	{
		if (!player->IsInvincible())
		{
			player->SetPosition({ static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2) });
			player->TakeDamage();
		}
	}
}

void Enemy::Update() 
{
	if (!target->IsInvincible())
	{
		Vector2 direction = Vector2Subtract(target->GetPosition(), position);
		velocity = Vector2Normalize(direction);
		position = Vector2Add(position, Vector2Scale(velocity, speed * deltaT));

		CheckOutOfBounds(position, width, height);
	}
}

void Enemy::Draw()
{
	DrawRectangleV(position, { width, height }, RED);
}

void CheckOutOfBounds(Vector2& position, float width, float height)
{
	if (position.x < 0.0f)
	{
		position.x = 0.0f;
	}
	else if (position.x + width > static_cast<float>(GetScreenWidth()))
	{
		position.x = static_cast<float>(GetScreenWidth()) - width;
	}
	if (position.y < 0.0f)
	{
		position.y = 0.0f;
	}
	else if (position.y + height > static_cast<float>(GetScreenHeight()))
	{
		position.y = static_cast<float>(GetScreenHeight()) - height;
	}
}