#pragma once
#include "Collectible.h"

class ExtraLife : public Collectible
{
private:

public:

	ExtraLife(Vector2 pos, int texID, float width, float height);
	~ExtraLife() {}
	void WasCollected(Player* player) override;
	void Update() override;
	void Draw() override;

};

