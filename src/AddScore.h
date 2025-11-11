#pragma once
#include "Collectible.h"

class AddScore : public Collectible
{
private:

	int valueToAdd;

	float timer;

public:

	AddScore(Vector2 pos, int texID, float width, float height);
	~AddScore() {}

	void WasCollected(Player* player) override;
	void Update() override;
	void Draw() override;
};

