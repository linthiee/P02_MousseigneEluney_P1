#pragma once
#include "Collectible.h"

class ScoreMultiplyer : public Collectible
{
private:

	int multiplierValue;

	float timer;

public:

	ScoreMultiplyer(Vector2 pos, int texID, float width, float height);
	~ScoreMultiplyer() {}

	void WasCollected(Player* player) override;
	void Update() override;
	void Draw() override;

};

