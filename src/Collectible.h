#pragma once
#include "Entity.h"
#include "Player.h"

class Collectible : public Entity
{
private:

public:
	Collectible(Vector2 pos, int texID, float width, float height);
	~Collectible() {}

	virtual void WasCollected(Player* player);
	void IsCollidingWith(Entity* otherEntity) override;

	void Update() override;
	void Draw() override;
};