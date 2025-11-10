#include "Player.h"
#include "globals.h"
#include "collectible.h"

#include "raymath.h"

static void CheckOutOfBounds(Vector2& position, float width, float height);

Player::Player(Vector2 pos, int texID, float width, float height) : Entity(pos, texID, width, height)
{
	lives = 3;
	score = 0;
	velocity = { 0.0f, 0.0f };
	speed = 50.0f;
	baseSpeed = speed;

	position = pos;

	textureID = texID;

	this->width = width;
	this->height = height;

	manager = nullptr;

	isInvincible = false;
	invincibilityTimer = 0.0f;
	invincibilityDuration = 2.0f;
}

void Player::SetStateManager(StateManager* stateManager)
{
	manager = stateManager;
}

int Player::GetLife()
{
	return lives;
}

void Player::UpdateLife(int life)
{
	lives+= life;
}

void Player::IsCollidingWith(Entity* otherEntity)
{
	Collectible* item = dynamic_cast<Collectible*>(otherEntity);
	if (item != nullptr)
	{
		item->WasCollected(this);
		item->DeleteEntity();

		return; 
	}
}

void Player::TakeDamage()
{
	if (isInvincible)
	{
		return; 
	} 

	lives--;

	isInvincible = true;
	invincibilityTimer = invincibilityDuration;

	if (lives < 0)
	{
		lives = 0;
	}
}

bool Player::IsInvincible()
{
	return isInvincible;
}

void Player::ActivateScoreMultiplier(int multiplier, float duration)
{
	if (manager != nullptr)
	{
		manager->SetMultiplier(multiplier, duration);
	}
}

void Player::ActivateSpeedMultiplier(float multiplier, float duration)
{
	if (manager != nullptr)
	{
		manager->SetSpeedMultiplier(multiplier, duration);
	}
}

void Player::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}

float Player::GetBaseSpeed()
{
	return baseSpeed;
}

void Player::Update()
{
	if (isInvincible)
	{
		invincibilityTimer -= deltaT; 
		if (invincibilityTimer <= 0.0f)
		{
			isInvincible = false; 
		}
	}

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

	CheckOutOfBounds(position, width, height);
}

void Player::Draw()
{
	DrawRectangleV(position, { width, height }, BLUE);
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
