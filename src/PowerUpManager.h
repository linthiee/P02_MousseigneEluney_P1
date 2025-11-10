#pragma once
#include "Entity.h"

#include <vector>

class PowerUpManager
{
private:
    float intervalSpawn; 
    float spawnTimer;   

public:

    PowerUpManager(float spawnInterval);
    ~PowerUpManager() {};

    void Update(float deltaT, std::vector<Entity*>& entities, int currentPowerUpCount);
};