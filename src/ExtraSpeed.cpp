#include "ExtraSpeed.h"
#include "globals.h"

ExtraSpeed::ExtraSpeed(Vector2 pos, int texID, float width, float height) : Collectible(pos, texID, width, height)
{
	timer = 10.0f;        
	speedIncrease = 2.5f;     
	buffDuration = 5.0f;   
}

void ExtraSpeed::WasCollected(Player* player)
{
	player->ActivateSpeedMultiplier(speedIncrease, buffDuration);
}

void ExtraSpeed::Update()
{
	timer -= deltaT;

	if (timer <= 0.0f)
	{
		DeleteEntity();
	}
}

void ExtraSpeed::Draw()
{
	DrawRectangleGradientV(static_cast<int>(position.x), static_cast<int>(position.y), static_cast<int>(width), static_cast<int>(height), ORANGE, WHITE);
}
