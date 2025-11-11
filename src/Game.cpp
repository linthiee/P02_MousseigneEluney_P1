#include "Game.h"

#include "Collectible.h"  
#include "ExtraLife.h"
#include "ScoreMultiplyer.h"
#include "ExtraSpeed.h"
#include "globals.h"
#include "Enemy.h"

#include <ctime> 

Game::Game()
{
    InitWindow(screenWidth, screenHeight, "Parcial 02 Programacion 01");
    SetRandomSeed(static_cast<unsigned int>(time(nullptr)));

    player = new Player({ static_cast<float>(screenWidth / 2), static_cast<float>(screenHeight / 2) }, 0, 50.0f, 50.0f);
    entities.push_back(player);

    powerUpManager = new PowerUpManager(10.0f);
    stateManager = new StateManager(player);

    player->SetStateManager(stateManager);

    InitializeEnemyQuant();
}

Game::~Game()
{
    for (int i = 0; i < entities.size(); i++)
    {
        delete entities[i];
    }
    entities.clear();

    delete powerUpManager;
    delete stateManager;

    CloseWindow();
}

void Game::Run()
{
    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }
}

void Game::Update()
{
    UpdateDeltaTime();

    if (!stateManager->IsGameOver())
    {
        stateManager->Update();

        for (int i = 0; i < entities.size(); i++)
        {
            entities[i]->Update();
        }

        for (int i = 0; i < entities.size(); i++)
        {
            for (int j = i + 1; j < entities.size(); j++)
            {
                Entity* a = entities[i];
                Entity* b = entities[j];

                if (CollisionRectangles(a, b))
                {
                    a->IsCollidingWith(b);
                    b->IsCollidingWith(a);
                }
            }
        }

        int activePowerUps = 0;
        for (int i = static_cast<int>(entities.size()) - 1; i >= 0; i--)
        {
            if (entities[i]->IsEntityDeleted())
            {
                delete entities[i];
                entities.erase(entities.begin() + i);
            }
            else
            {
                if (dynamic_cast<Collectible*>(entities[i]) != nullptr)
                {
                    activePowerUps++;
                }
            }
        }

        powerUpManager->Update(deltaT, entities, activePowerUps);
    }
}

void Game::Draw()
{
    BeginDrawing();
    ClearBackground(GRAY);

    for (int i = 0; i < entities.size(); i++)
    {
        entities[i]->Draw();
    }

    stateManager->Draw();

    if (stateManager->IsGameOver())
    {
        Color color;
        color.a = 125;
        color.r = 0;
        color.g = 0;
        color.b = 0;

        DrawRectangle(0, 0, screenWidth, screenHeight, color);

        DrawText("GAME OVER", screenWidth / 2 - 100, 20, 40, RED);

        if (hasWon)
        {
            DrawText("YOU WON!", screenWidth / 2 - 80, 100, 30, GREEN);
        }
        else
        {
            DrawText("YOU LOSE!", screenWidth / 2 - 80, 100, 30, RED);
        }

        DrawText(TextFormat("Final Score: %i", static_cast<int>(stateManager->GetScore())), screenWidth / 2 - 100, 160, 20, WHITE);
    }

    EndDrawing();
}

void Game::UpdateDeltaTime()
{
    deltaT = GetFrameTime();
}

void Game::InitializeEnemyQuant()
{
    int enemyQuant = GetRandomValue(3, 4);

    float enemyWidth = 50.0f;
    float enemyHeight = 50.0f;

    for (int i = 0; i < enemyQuant; i++)
    {
        Vector2 spawnPos = GetSafeSpawnPosition(enemyWidth, enemyHeight);
        Enemy* enemy = new Enemy(spawnPos, 0, enemyWidth, enemyHeight, player);

        entities.push_back(enemy);
    }
}

bool Game::CollisionRectangles(Entity* a, Entity* b)
{
    return (a->GetPosition().x < b->GetPosition().x + b->GetWidth() &&
        a->GetPosition().x + a->GetWidth() > b->GetPosition().x &&
        a->GetPosition().y < b->GetPosition().y + b->GetHeight() &&
        a->GetPosition().y + a->GetHeight() > b->GetPosition().y);
}

bool Game::CheckRectCollision(Vector2 posA, float widthA, float heightA, Vector2 posB, float widthB, float heightB)
{
    return (posA.x < posB.x + widthB &&
        posA.x + widthA > posB.x &&
        posA.y < posB.y + heightB &&
        posA.y + heightA > posB.y);
}

bool Game::IsCollidingWithAny(Vector2 newPos, float newWidth, float newHeight)
{
    for (int i = 0; i < entities.size(); i++)
    {
        Entity* existingEntity = entities[i];

        if (CheckRectCollision(newPos, newWidth, newHeight, existingEntity->GetPosition(), existingEntity->GetWidth(), existingEntity->GetHeight()))
        {
            return true;
        }
    }
    return false;
}

Vector2 Game::GetSafeSpawnPosition(float newWidth, float newHeight)
{
    Vector2 newPos = { 0, 0 };

    bool isSafe = false;

    int attempts = 0;

    do
    {
        int spawnChance = GetRandomValue(1, 100);

        if (spawnChance <= 25)
        {
            newPos = { static_cast<float>(GetRandomValue(0, 800)), 0.0f };
        }
        else if (spawnChance <= 50)
        {
            newPos = { static_cast<float>(GetRandomValue(0, 800)), 450.0f };
        }
        else if (spawnChance <= 75)
        {
            newPos = { 0.0f, static_cast<float>(GetRandomValue(0, 450)) };
        }
        else
        {
            newPos = { 800.0f, static_cast<float>(GetRandomValue(0, 450)) };
        }

        isSafe = !IsCollidingWithAny(newPos, newWidth, newHeight);
        attempts++;

    } while (!isSafe && attempts < 100);

    return newPos;
}