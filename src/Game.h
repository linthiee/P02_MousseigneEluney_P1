#pragma once

#include "raylib.h"

#include "Entity.h"
#include "Player.h"
#include "StateManager.h"
#include "PowerUpManager.h"

#include <vector>

class Game
{
private:
    std::vector<Entity*> entities;
    Player* player;
    StateManager* stateManager;
    PowerUpManager* powerUpManager;

    void Update();
    void Draw();

    void UpdateDeltaTime();
    void InitializeEnemyQuant();
    
    bool CollisionRectangles(Entity* a, Entity* b);
    bool CheckRectCollision(Vector2 posA, float widthA, float heightA, Vector2 posB, float widthB, float heightB);
    bool IsCollidingWithAny(Vector2 newPos, float newWidth, float newHeight);
    Vector2 GetSafeSpawnPosition(float newWidth, float newHeight);


public:
    Game();
    ~Game();

    void Run();
};