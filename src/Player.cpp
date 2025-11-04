#include "Player.h"
#include "globals.h"

#include "raymath.h"

Player::Player(Vector2 pos, int texID, float width, float height) : Entity(pos, texID, width, height)
{
	life = 100.0f;
	score = 0;
	velocity = { 0.0f, 0.0f };
	speed = 50.0f;
	
	position = pos;

	textureID = texID;

	this->width = width;
	this->height = height;
}

//void Player::IsCollidingWith(Entity* otherEntity)
//{
//}

void Player::Update()
{
	velocity = { 0.0f, 0.0f };

	if (IsKeyDown(KEY_UP))
	{
		velocity.y -= 1.0f;
	}
	if (IsKeyDown(KEY_LEFT))
	{
		velocity.x -= 1.0f;
	}
	if (IsKeyDown(KEY_RIGHT))
	{
		velocity.x += 1.0f;
	}
	if (IsKeyDown(KEY_DOWN))
	{
		velocity.y += 1.0f;
	}

	position = Vector2Add(position, Vector2Scale(Vector2Normalize(velocity), speed * deltaT));
}

void Player::Draw()
{
	DrawRectangleV(position, { width, height }, BLUE);
}
