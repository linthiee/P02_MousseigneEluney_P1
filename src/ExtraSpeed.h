#pragma once
#include "Collectible.h"

class ExtraSpeed : public Collectible
{
private:

	float speedIncrease;
	float timer;
	float buffDuration;

public:

	ExtraSpeed(Vector2 pos, int texID, float width, float height);
	~ExtraSpeed() {}

	void WasCollected(Player* player) override;

	void Update() override;
	void Draw() override;
};

